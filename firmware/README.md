# Raijin Firmware
The firmware controls when the Raspberry Pi Pico 2 W device emits a sound and lights the 3 LED strips. It is written in vanilla C.
It should also work on other boards in the Pico series, though none of them have been tested - see
[Other boards in the Pico series](#other-boards-in-the-pico-series) below.

The easiest way to get started is to first install VS Code with the Raspberry Pi Pico extension. 
[See the official C/C++ SDK documentation](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)

## Build
Within VS Code File -> Open Folder -> Select firmware directory
You should be prompted if you want to import this as a Pico project. Click Yes.
If you have successfully installed the Raspberry Pi Pico extension the VS Code UI will show "Compile" and "Run" buttons
along the bottom right. Simply click "Compile" to build the code

## Other boards in the Pico series

The Pico 2 W is what this was built and tested on, but nothing in the firmware is specific to it.
Building for another board in the series is two lines at the top of `CMakeLists.txt`:

```cmake
set(PICO_BOARD pico2_w CACHE STRING "Board type")
set(PICO_PLATFORM rp2350 CACHE STRING "Platform")
```

For the original Pico, that is `pico` and `rp2040`. They are cache variables without `FORCE`, so
passing `-DPICO_BOARD=pico -DPICO_PLATFORM=rp2040` to a fresh build directory works just as well and
leaves the file alone.

Nothing else should need changing:

* The PIO clock divider is computed at runtime from `clock_get_hz(clk_sys)`, so it follows whatever
  the system clock happens to be — 125 MHz on an RP2040 rather than 150 MHz.
* `pico_rand` supports the RP2040. With no hardware TRNG it seeds and stirs from the ring oscillator,
  the microsecond timer, a bus performance counter and a hash of RAM instead.
* The audio is 22 KB, so the original Pico's 2 MB of flash is ample. Only the budget table in
  `audio-design.md` assumes 4 MB, and it only matters if you load much longer clips.
* The boards are pin-compatible, so the wiring and `hardware/assembly.md` are unchanged.

None of the radio variants' Wi-Fi is used — the firmware links `pico_stdlib`, `pico_rand`,
`hardware_pio` and `hardware_dma`, and never brings up `cyw43`. A non-W board is fine and cheaper.

If you build on something else, the thing to listen for is the audio, since that is what the clock and bus timing affect.

## Changing the audio files

Replace the WAV in `audio/` and rebuild. Any sample rate, mono or stereo,
8/16/24/32-bit PCM or 32-bit float — the converter normalises all of it. Nothing
else needs editing; the clip table is generated.

Keep it to one file. The converter happily builds a table of several, but
`main.c` plays `audio_clips[0]` and ignores the rest, and the unused clips still
take up flash. If your replacement is not 500 ms long, change `BURST_MS` in
`src/main.c` to match — the flash duration is set there, not taken from the clip.

To change the playback rate: `cmake -B build -DAUDIO_RATE=16000`.

## Flashing the firmware
While holding down the "BOOTSEL" button on the Pico plug the Pico into your computer using an appropriate micro USB cable.
You can now click the "Run" button at the bottom right hand side of the VS Code UI.

With the firmware flashed you can remove the micro USB cable and close up the enclosure.

Switch the device on and it should start flashing the strips and playing the noise burst together for half a second,
then waiting a random 2-6 seconds before doing it again.

## Stimulus timing

The loop lives at the bottom of `src/main.c` and is controlled by three constants
at the top of that file:

| Constant          | Value | Meaning                                    |
|-------------------|-------|--------------------------------------------|
| `BURST_MS`        | 500   | strips lit and noise playing, together     |
| `INTERVAL_MIN_MS` | 2000  | burst onset to burst onset, at least       |
| `INTERVAL_MAX_MS` | 6000  | burst onset to burst onset, less than      |

The interval is redrawn every cycle, uniform over 2000-5999 ms, from
`get_rand_32()` — the RP2350 hardware entropy source, so the sequence differs on
every power-up. The burst is subtracted from it before sleeping, so the dark,
silent stretch between bursts is 1500-5499 ms.

This follows [Mr FlashyBeepy](https://github.com/Watty-Git/mrflashybeepy), an
Arduino build of the training device described in Rowland, Bushnell, Duncan and
Stein, "Ameliorating Hemianopia with Multisensory Training", *Journal of
Neuroscience* 43(6):1018-1026 (2023). `audio/burst-500ms.wav` is their noise
burst, generated with `sox -q -n burst-500ms.wav synth noise delay 0 remix - fade 0 0.5 0 norm -1`.

One deliberate difference from their sketch: their `delay(interval)` runs after
the burst, so their 2-6 s is the off time and their bursts land 2.5-6.5 s apart.
The paper and their own README both describe the interval between stimuli as
2-6 s, so `BURST_MS` is subtracted from the wait here.

The amp settle before the first sample and the tail silence drained after the
last both sit outside the flash window, which adds about 28 ms to each cycle.

## Files

```
CMakeLists.txt          build; runs the converter, generates the PIO header
pico_sdk_import.cmake   stock SDK bootstrap
tools/wav2flash.py      WAV -> mono PCM + clips.S/.c/.h  (pure stdlib)
src/i2s.pio             PIO I2S transmitter
src/audio.h/.c          DMA ping-pong player, volume, fades, amp mute
src/main.c              boot, then the stimulus loop: flash + burst, random interval, repeat
audio/burst-500ms.wav   the 500 ms white noise burst, from the Mr FlashyBeepy repo
```