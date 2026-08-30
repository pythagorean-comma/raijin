# Raijin Firmware
The firmware controls when the Raspberry Pi Pico 2 W device emits a sound and lights the 3 LED strips. It is written in vanilla C.
It should in theory also work on other variants in the Pico series but these have not been tested.

The easiest way to get started is to first install VS Code with the Raspberry Pi Pico extension. 
[See the official C/C++ SDK documentation](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)

## Build
Within VS Code File -> Open Folder -> Select firmware directory
You should be prompted if you want to import this as a Pico project. Click Yes.
If you have successfully installed the Raspberry Pi Pico extension the VS Code UI will show "Compile" and "Run" buttons
along the bottom right. Simply click "Compile" to build the code

## Changing the audio files

Drop your WAVs into `audio/` and rebuild. Any sample rate, mono or stereo,
8/16/24/32-bit PCM or 32-bit float — the converter normalises all of it. Nothing
else needs editing; the clip table is generated.

To change the playback rate: `cmake -B build -DAUDIO_RATE=16000`.

## Flashing the firmware
While holding down the "BOOTSEL" button on the Pico plug the Pico into your computer using an appropriate micro USB cable.
You can now click the "Run" button at the bottom right hand side of the VS Code UI.

With the firmware flashed you can remove the micro USB cable and close up the enclosure.

Switch the device on using the toggle switch and it should start emitting the WAV audio and the LEDs illuminate at 
semi-random intervals.

## Files

```
CMakeLists.txt          build; runs the converter, generates the PIO header
pico_sdk_import.cmake   stock SDK bootstrap
tools/wav2flash.py      WAV -> mono PCM + clips.S/.c/.h  (pure stdlib)
src/i2s.pio             PIO I2S transmitter
src/audio.h/.c          DMA ping-pong player, volume, fades, amp mute
src/main.c              boot, then: play a clip, idle 30 s, repeat
audio/*.wav             synthesised placeholders — replace with yours
```