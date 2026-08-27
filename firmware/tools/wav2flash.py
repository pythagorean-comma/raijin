#!/usr/bin/env python3
"""
wav2flash.py -- convert WAV files into flash-resident PCM blobs for the Pico 2 W.

Output per input file:
  <outdir>/<name>.pcm   raw signed 16-bit little-endian mono PCM at --rate
And, once for the whole set:
  <outdir>/clips.S      GNU-as stub that .incbin's every .pcm into .rodata (i.e. flash)
  <outdir>/clips.h      extern declarations + a clip table + a flash budget report

Pure stdlib -- no numpy, no ffmpeg. Handles 8/16/24/32-bit PCM and 32-bit float
WAVs, mono or multi-channel, at any input sample rate.

Usage:
    python3 tools/wav2flash.py --rate 22050 --outdir build/generated audio/*.wav
"""

import argparse
import os
import struct
import sys
import wave
from array import array


# ---------------------------------------------------------------- WAV reading

def _read_with_wave_module(path):
    """Return (samples: array('i') interleaved, channels, rate, sampwidth)."""
    with wave.open(path, "rb") as w:
        ch, width, rate, nframes = (
            w.getnchannels(), w.getsampwidth(), w.getframerate(), w.getnframes()
        )
        raw = w.readframes(nframes)
    return raw, ch, rate, width, "pcm"


def _read_raw_riff(path):
    """Fallback parser: needed for WAVE_FORMAT_EXTENSIBLE / float WAVs that the
    stdlib wave module refuses to open."""
    with open(path, "rb") as f:
        data = f.read()
    if data[:4] != b"RIFF" or data[8:12] != b"WAVE":
        raise ValueError(f"{path}: not a RIFF/WAVE file")
    pos, fmt, raw = 12, None, None
    while pos + 8 <= len(data):
        cid = data[pos:pos + 4]
        (csz,) = struct.unpack_from("<I", data, pos + 4)
        body = data[pos + 8:pos + 8 + csz]
        if cid == b"fmt ":
            fmt = body
        elif cid == b"data":
            raw = body
        pos += 8 + csz + (csz & 1)          # chunks are word-aligned
    if fmt is None or raw is None:
        raise ValueError(f"{path}: missing fmt or data chunk")
    tag, ch, rate, _, _, bits = struct.unpack_from("<HHIIHH", fmt, 0)
    if tag == 0xFFFE and len(fmt) >= 40:    # EXTENSIBLE -> real tag in SubFormat
        tag = struct.unpack_from("<H", fmt, 24)[0]
    kind = "float" if tag == 3 else "pcm"
    if tag not in (1, 3):
        raise ValueError(f"{path}: unsupported WAV format tag {tag}")
    return raw, ch, rate, bits // 8, kind


def read_wav(path):
    try:
        return _read_with_wave_module(path)
    except (wave.Error, EOFError):
        return _read_raw_riff(path)


def to_int16_mono(raw, channels, width, kind):
    """Decode raw frame bytes -> array('h') of mono samples, averaging channels."""
    n = len(raw) // width
    if kind == "float":
        if width != 4:
            raise ValueError("only 32-bit float WAV is supported")
        vals = array("f")
        vals.frombytes(raw[:n * 4])
        samples = [max(-32768, min(32767, int(v * 32767.0))) for v in vals]
    elif width == 1:                        # 8-bit WAV is unsigned
        samples = [(b - 128) << 8 for b in raw[:n]]
    elif width == 2:
        a = array("h")
        a.frombytes(raw[:n * 2])
        if sys.byteorder == "big":
            a.byteswap()
        samples = a
    elif width == 3:
        samples = [
            int.from_bytes(raw[i:i + 3], "little", signed=True) >> 8
            for i in range(0, n * 3, 3)
        ]
    elif width == 4:
        a = array("i")
        a.frombytes(raw[:n * 4])
        if sys.byteorder == "big":
            a.byteswap()
        samples = [v >> 16 for v in a]
    else:
        raise ValueError(f"unsupported sample width {width}")

    if channels == 1:
        return array("h", samples)
    out = array("h", bytes(2 * (len(samples) // channels)))
    for i in range(len(out)):
        acc = 0
        base = i * channels
        for c in range(channels):
            acc += samples[base + c]
        out[i] = acc // channels
    return out


# ------------------------------------------------------------------ resample

def resample(src, src_rate, dst_rate):
    """Linear interpolation. Good enough once the source is low-passed by the
    ~10 kHz bandwidth of a small speaker; run a proper SRC offline if you care."""
    if src_rate == dst_rate or not src:
        return src
    ratio = src_rate / dst_rate
    n_out = int(len(src) / ratio)
    out = array("h", bytes(2 * n_out))
    for i in range(n_out):
        pos = i * ratio
        j = int(pos)
        frac = pos - j
        a = src[j]
        b = src[j + 1] if j + 1 < len(src) else a
        out[i] = int(a + (b - a) * frac)
    return out


def normalise(samples, target_dbfs):
    peak = max((abs(s) for s in samples), default=0)
    if peak == 0:
        return samples
    target = 32767 * (10.0 ** (target_dbfs / 20.0))
    gain = target / peak
    return array("h", (max(-32768, min(32767, int(s * gain))) for s in samples))


# ------------------------------------------------------------------ emitters

def c_ident(path):
    stem = os.path.splitext(os.path.basename(path))[0]
    ident = "".join(ch if ch.isalnum() else "_" for ch in stem).lower()
    return ident if ident[0].isalpha() or ident[0] == "_" else "clip_" + ident


HEADER_TMPL = '''\
/* Generated by tools/wav2flash.py -- do not edit. */
#pragma once
#include <stdint.h>

/* Every clip lives in .rodata, which the linker places in the memory-mapped
 * XIP flash window at 0x10000000. Nothing is copied to RAM at boot. */

#define CLIP_SAMPLE_RATE {rate}u
#define CLIP_COUNT       {count}u

typedef struct {{
    const int16_t *samples;   /* mono, signed 16-bit, CLIP_SAMPLE_RATE Hz */
    uint32_t       length;    /* number of samples */
    const char    *name;
}} audio_clip_t;

{externs}
extern const audio_clip_t audio_clips[CLIP_COUNT];

/* Flash budget
{budget}
 */
'''


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("inputs", nargs="+", help="input .wav files")
    ap.add_argument("--outdir", required=True)
    ap.add_argument("--rate", type=int, default=22050,
                    help="target sample rate in Hz (default 22050)")
    ap.add_argument("--normalize", type=float, default=None, metavar="DBFS",
                    help="peak-normalise each clip to this dBFS, e.g. -3")
    ap.add_argument("--flash-bytes", type=int, default=4 * 1024 * 1024)
    ap.add_argument("--reserve-bytes", type=int, default=640 * 1024,
                    help="flash to leave for code (default 640 KiB)")
    args = ap.parse_args()

    os.makedirs(args.outdir, exist_ok=True)
    clips, asm, externs, budget, total = [], [], [], [], 0

    for path in sorted(args.inputs):
        raw, ch, rate, width, kind = read_wav(path)
        mono = to_int16_mono(raw, ch, width, kind)
        mono = resample(mono, rate, args.rate)
        if args.normalize is not None:
            mono = normalise(mono, args.normalize)

        ident = c_ident(path)
        pcm_path = os.path.abspath(os.path.join(args.outdir, ident + ".pcm"))
        with open(pcm_path, "wb") as f:
            f.write(mono.tobytes())

        nbytes = len(mono) * 2
        total += nbytes
        secs = len(mono) / args.rate

        asm.append(
            f'    .section .rodata.{ident}, "a"\n'
            f'    .balign 4\n'
            f'    .global {ident}_pcm\n'
            f'{ident}_pcm:\n'
            f'    .incbin "{pcm_path}"\n'
        )
        externs.append(f"extern const int16_t {ident}_pcm[];")
        clips.append((ident, len(mono), os.path.basename(path)))
        budget.append(f" *   {os.path.basename(path):<24} "
                      f"{secs:6.2f} s  {nbytes:>9,} bytes")
        print(f"  {os.path.basename(path):<24} {rate} Hz {ch}ch/{width*8}-bit "
              f"-> {args.rate} Hz mono  {secs:6.2f} s  {nbytes:,} bytes")

    available = args.flash_bytes - args.reserve_bytes
    budget.append(f" *   {'TOTAL':<24} {'':>6}    {total:>9,} bytes "
                  f"({100.0 * total / available:.1f}% of the "
                  f"{available:,}-byte audio budget)")

    with open(os.path.join(args.outdir, "clips.S"), "w") as f:
        f.write("/* Generated by tools/wav2flash.py -- do not edit. */\n")
        f.write("".join(asm))

    table = ",\n".join(
        f'    {{ {i}_pcm, {n}u, "{src}" }}' for i, n, src in clips
    )
    with open(os.path.join(args.outdir, "clips.h"), "w") as f:
        f.write(HEADER_TMPL.format(rate=args.rate, count=len(clips),
                                   externs="\n".join(externs),
                                   budget="\n".join(budget)))
    with open(os.path.join(args.outdir, "clips.c"), "w") as f:
        f.write('/* Generated by tools/wav2flash.py -- do not edit. */\n'
                '#include "clips.h"\n\n'
                f"const audio_clip_t audio_clips[CLIP_COUNT] = {{\n{table}\n}};\n")

    print(f"\n  total {total:,} bytes of audio "
          f"({100.0 * total / available:.1f}% of the {available:,}-byte budget)")
    if total > available:
        print("  WARNING: audio exceeds the flash budget", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
