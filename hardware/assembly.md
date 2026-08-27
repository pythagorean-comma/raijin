# Raijin Assembly

## Bill of Materials

| Item                                                        | Description | Quantity | Link                                                                                                         |
|-------------------------------------------------------------|-------------|----------|--------------------------------------------------------------------------------------------------------------|
| Raspberry Pi Pico 2 W, headers fitted                       |             | 1        | [The Pi Hut](https://thepihut.com/products/raspberry-pi-pico-2-w?variant=54063378760065)                     |
| Freenove FNK0081 Breakout Board for Pico                    |             | 1        | [Freenove Store](https://store.freenove.com/products/fnk0081)                                                |
| Adafruit ADA3006 MAX98357A amplifier                        |             | 1        | [The Pi Hut](https://thepihut.com/products/adafruit-i2s-3w-class-d-amplifier-breakout-max98357a)             |
| Speaker, 4 Ω 3 W, flying leads                              |             | 1        | [The Pi Hut](https://thepihut.com/products/mono-enclosed-speaker-with-plain-wires-3w-4-ohm)                  |
| DFRobot DFR0457 Gravity MOSFET Power Controller             |             | 1        | [The Pi Hut](https://thepihut.com/products/gravity-mosfet-power-controller)                                  |
| PAUTIX 5 V COB strip, 2 m                                   |             | 1        | [Amazon](https://www.amazon.co.uk/dp/B08XBW48K9?th=1)                                                        |
| USB-A male to bare-wire pigtail                             |             | 1        |                                                                                                              |
| WAGO 221-415 (5-way)                                        |             | 2        | [CPC](https://cpc.farnell.com/wago/221-415/compact-lever-connector-5-way/dp/CN20137)                         |
| WAGO 221-412 (2-way)                                        |             | 4        | [CPC](https://cpc.farnell.com/wago/221-412/compact-lever-connector-2-way/dp/CN20135)                         |
| Belkin BoostCharge 10K (BPB011)                             |             | 1        | [Belkin](https://www.belkin.com/uk/p/power-bank-10k/BPB011btBK.html)                                         |
| Panasonic EEUFR1A102L, 1000 µF 10 V                         |             | 1        | [CPC](https://cpc.farnell.com/panasonic/eeufr1a102l/capacitor-radial-10v-1000uf/dp/CA07459)                  |
| 1N5817 Schottky                                             |             | 1        | [CPC](https://cpc.farnell.com/taiwan-semiconductor/1n5817/schottky-rectifier-1a-20v-do-204al/dp/SC21533)     |
| Illuminated toggle switch with cover                        |             | 1        | [The Pi Hut](https://thepihut.com/products/illuminated-toggle-switch-with-cover-red)                         |
| 6.3 mm insulated spade crimps                               |             | 3        | [The Pi Hut](https://thepihut.com/products/spade-quick-connector-kit-6-3mm-4-8mm-2-8mm)                      |
| Hookup wire for signals, 7/0.2 mm (0.22 mm², approx 24 AWG) |             |          | [CPC](https://cpc.farnell.com/concordia-technologies/ew7-0-2blk10m/equipment-wire-7-0-20mm-black/dp/CB19933) |
| Bootlace ferrules and crimper                               |             |          |                                                                                                              |
| Hammond 1556GAWH ABS box                                    |             | 1        | [RS Components](https://uk.rs-online.com/web/p/general-purpose-enclosures/2777586)                           |
| Micro-USB cable                                             |             | 1        |                                                                                                              |

## Wiring
![Wiring Diagram](wiring.svg)

### Wiring the power bank to the switch

#### USB-A male to bare-wire pigtail 
A USB-A male to bare-wire pigtail is  USB-A male plug with bare wires on the other end. Sold as a "USB power pigtail" 
or "USB-A to open end". These can easily be made by utting the small end off any cheap USB cable.

A full USB cable has four conductors. Nominally red for +5 V, black for ground, and white and green for data. 
You want only the first two. Cut the data pair back and heatshrink them individually to avoid having bare data wires 
which could short against a terminal.

#### Making the connections
1. Drill a hole in the Hammond 1556GAWH ABS box and mount the switch
2. Crimp three 6.3 mm female insulated spades — pigtail red, a wire to the +5 V WAGO, and a wire to a spare GND terminal on the Pico board. Strip 5–6 mm, crimp, and tug each one firmly. A good spade takes deliberate force to pull off.
3. Push them on: pigtail red to the supply terminal, the +5 V WAGO wire to the switched output, the ground wire to the LED terminal.
4. Test before going further. Plug the pigtail into the bank, put the meter across the switched output and the pigtail's black wire: 0 V with the switch off, about 5 V with it on, and the switch's own lamp should light. Only now connect anything to the WAGO.
5. Anchor the pigtail with a cable tie base near the switch, so tugging the power bank never pulls on a spade terminal.