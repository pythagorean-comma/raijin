# Flash-resident WAV playback on the Raspberry Pi Pico 2 W

A Pico 2 W has 4 MB of QSPI flash and the firmware itself is well under 1 MB, so a handful of 10-second clips fit with room
to spare. The clips are linked into `.rodata`, which lives in the memory-mapped
XIP flash window at `0x10000000` — so they cost **zero RAM**; the DMA/CPU reads
them in place.

This project is a complete, building reference implementation. It was compiled
against pico-sdk 2.3.0 for `PICO_BOARD=pico2_w` and the PIO frame format was
verified by simulation.

## Flash budget

16-bit mono PCM at various rates, per 10-second clip:

| Sample rate   | Per clip   | 5 clips    | Verdict                            |
|---------------|------------|------------|------------------------------------|
| 44 100 Hz     | 882 KB     | 4.3 MB     | doesn't fit                        |
| 32 000 Hz     | 640 KB     | 3.1 MB     | tight                              |
| **22 050 Hz** | **441 KB** | **2.2 MB** | **comfortable — the default here** |
| 16 000 Hz     | 320 KB     | 1.6 MB     | plenty of headroom                 |

Measured from the build in this repo (two 10 s clips at 22.05 kHz):

```
text 916,036   data 0   bss 4,744
.rodata  882,092 bytes @ 0x10005df8   <- both clips, in flash
buf        2,048 bytes @ 0x200017f8   <- the entire RAM cost of playback
```

Roughly 895 KB of 4 MB used. You have ~3 MB of audio headroom even after leaving
generous room for the CYW43 Wi-Fi/BT stack.

Two things make this cheap:

* **Mono, not stereo.** The clips are stored mono and duplicated to both I2S
  channels on the fly. Storing pre-interleaved stereo would double the flash for
  no benefit through one speaker.
* **No WAV headers or decoding.** The build converts to raw PCM; the firmware
  never parses a RIFF file.

If you ever need more, IMA ADPCM gets you 4:1 with a ~20-line decoder, and Opus
via `libopus` fixed-point gets 20:1 but wants a lot more code space and CPU.

## Hardware

| MAX98357A | Pico 2 W | Notes                                                 |
|-----------|----------|-------------------------------------------------------|
| `BCLK`    | GP16     | side-set pin 0                                        |
| `LRC`     | GP17     | must be `BCLK + 1` — PIO side-set needs them adjacent |
| `DIN`     | GP18     | any free GPIO                                         |
| `SD`      | GP19     | driven low between clips to kill idle hiss            |
| `VIN`     | VSYS/3V3 | 5 V gives noticeably more output                      |
| `GND`     | GND      |                                                       |

Leave `GAIN` floating for 9 dB. Pin assignments are `#define`s at the top of
`src/audio.h`.

`GP20`, `GP21` and `GP22` drive channels A, B and C of a MonkMakes Mosfetti, one
LED strip each. All three go high together for the length of each clip and low
between them, in step with the amp mute. Each channel is a low-side switch on its
own strip's negative; the gates are driven straight from the GPIOs, so no logic
supply is needed. See `hardware/assembly.md` for the wiring.


## How it works

```
audio/*.wav
   |  tools/wav2flash.py, run by CMake at build time
   |  decode -> mono -> resample -> peak-normalise
   v
build/generated/*.pcm  + clips.S (.incbin) + clips.c (the clip table)
   |  linker
   v
.rodata in XIP flash at 0x10000000        <- no RAM cost
   |  CPU, in the DMA completion IRQ: mono->stereo, volume, 5 ms edge fades
   v
two 1 KiB ping-pong buffers in RAM
   |  DMA, paced by the PIO TX DREQ
   v
PIO state machine -> BCLK / LRCLK / DIN -> MAX98357A -> speaker
```

The CPU wakes once per buffer — every 11.6 ms at 22.05 kHz — to convert 256
samples. That is a fraction of a percent of one core; everything else is DMA.

### `src/i2s.pio`

Standard Philips I2S. Every bit is exactly 2 PIO cycles (BCLK low, BCLK high)
and a stereo frame is 32 bits, so `pio_clock = 64 × sample_rate`. There are no
idle cycles in the loop, so BCLK is continuous and the frame period is exact.

The LRCLK edge deliberately lands on the *last* bit of the preceding word rather
than the first bit of the new one. That one-BCLK offset is what distinguishes
I2S from left-justified format, and it is what the MAX98357A expects. The FIFO
is fed `(left << 16) | (right & 0xffff)`, MSB first.

(`left` and `right` are pioasm keywords, hence the `lchan`/`rchan` labels.)

### Click and pop suppression

Two measures, both worth keeping:

* The amp's `SD` pin is held low except while a clip is playing. A class-D amp
  left enabled on a silent input hisses audibly.
* Every clip gets a 5 ms linear fade in and out during the buffer fill. Without
  it, the step from silence to the first sample is a sharp click.

There is also a 5 ms settling delay after un-muting, and two buffers of silence
flushed after the last sample so the amp is never muted mid-waveform.

## Things you may want to change

**Underrun margin.** The PIO TX FIFO is 8 entries deep, so the DMA restart in
the IRQ has ~360 µs of slack at 22.05 kHz. That is a huge margin. If you push to
48 kHz *and* run heavy Wi-Fi work on the same core, switch to two DMA channels
chained to each other — then the restart is in hardware and the margin is
irrelevant.

**Clock jitter.** At the default 150 MHz system clock the PIO divider for
22.05 kHz is 106.29, so the fractional divider dithers BCLK slightly. Inaudible
through a small speaker, but if you want it exact, set the system clock to a
multiple of `64 × Fs` (e.g. 149.5872 MHz = 106 × 64 × 22050). USB still works —
it clocks off PLL_USB.

**Wi-Fi coexistence.** `cyw43` work and flash reads share the bus. If you see
dropouts once Wi-Fi is up, either pin the audio IRQ to core 1 or raise
`AUDIO_BUF_FRAMES`.

**Alternatives to linking clips in.** If you'd rather update audio without
reflashing the firmware, you can reserve a flash region and write clips there
with `picotool load -o <offset>`, or put a small filesystem (littlefs) on the
tail of flash. Both cost more code and more complexity; embedding is the right
default for a fixed set of 1–5 clips.
