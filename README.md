# Raijin

Hardware design and firmware for a small battery-powered box that emits a sound and a light
simultaneously, at intervals of a few seconds. It is built around the
[Raspberry Pi Pico 2](https://www.raspberrypi.com/products/raspberry-pi-pico-2/), a very low cost ($7) and widely 
available microcontroller board. This build uses the Wi-Fi variant, the Pico 2 W. The firmware should
also run on the original Pico with a two-line build change, though that has not been tested.

It is an implementation of the training device described in Rowland, Bushnell, Duncan and Stein,
"Ameliorating Hemianopia with Multisensory Training", *Journal of Neuroscience* 43(6):1018-1026
(2023) — [paper](https://doi.org/10.1523/JNEUROSCI.0962-22.2022),
[free full text](https://pmc.ncbi.nlm.nih.gov/articles/PMC9908311/). In that study two patients
with long-standing hemianopia following a stroke recovered visual sensitivity after repeated
exposure to simultaneous flashes and noise bursts in their blind hemifield.

## This is a research device

It is not a medical device. It has not been tested, certified or approved by anybody, it makes no
claim to reproduce the study's results, and nothing here is medical advice. The paper reports two
patients. Talk to a clinician before using it for anything.

## Where things are

* [hardware/assembly.md](hardware/assembly.md) — bill of materials, wiring and assembly
* [firmware/README.md](firmware/README.md) — building, flashing and the stimulus timing
* [firmware/audio-design.md](firmware/audio-design.md) — how the audio playback works

## Credits

The stimulus timing and the white noise burst come from
[Mr FlashyBeepy](https://github.com/Watty-Git/mrflashybeepy), an Arduino build of the same device,
MIT licensed.
