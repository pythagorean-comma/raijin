# Raijin Assembly

## Bill of Materials

| Item                                            | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             | Quantity | Link                                                                                                           |
|-------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------|----------------------------------------------------------------------------------------------------------------|
| Raspberry Pi Pico 2 W, headers fitted           | Easiest to purchase the version with the headers fitted as we will be mounting this onto a breakout board.                                                                                                                                                                                                                                                                                                                                                                                              | 1        | [The Pi Hut](https://thepihut.com/products/raspberry-pi-pico-2-w?variant=54063378760065)                       |
| Freenove FNK0081 Breakout Board for Pico        | There are many breakout boards to choose from but this one gave the best documentation                                                                                                                                                                                                                                                                                                                                                                                                                  | 1        | [Freenove Store](https://store.freenove.com/products/fnk0081)                                                  |
| Adafruit ADA3006 MAX98357A amplifier            |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         | 1        | [The Pi Hut](https://thepihut.com/products/adafruit-i2s-3w-class-d-amplifier-breakout-max98357a)               |
| Speaker, 4 Ω 3 W, flying leads                  | The speaker will connect to the amplifier via a WAGO connector so be sure to get a speaker with cables that have bare ends                                                                                                                                                                                                                                                                                                                                                                              | 1        | [The Pi Hut](https://thepihut.com/products/mono-enclosed-speaker-with-plain-wires-3w-4-ohm)                    |
| DFRobot DFR0457 Gravity MOSFET Power Controller | The Pico has the control logic but it is the MOSFET controller which does the switching                                                                                                                                                                                                                                                                                                                                                                                                                 | 1        | [The Pi Hut](https://thepihut.com/products/gravity-mosfet-power-controller)                                    |
| PAUTIX 5 V COB strip, 2 m                       | We cut this into three 150 mm strips that sit side by side on the enclosure lid. The strip cuts every 12.5 mm, so 150 mm lands exactly on a mark. That uses 450 mm of the 2 m reel and leaves plenty spare for mistakes. The whole reel wants 5 V at 2 A, so about 1 A per metre, which puts the three strips together at 0.45 A. That is the figure used throughout the wiring tables.                                                                                                                 | 1        | [Amazon](https://www.amazon.co.uk/dp/B08XBW48K9?th=1)                                                          |
| USB-A male to bare-wire pigtail                 | In theory you can cut the end off a spare USB A cable you may have to hand but not all cables have just red and black so you are probably better off buying one                                                                                                                                                                                                                                                                                                                                         | 1        | [Amazon](https://www.amazon.co.uk/dp/B0CWNQB19C)                                                               |
| WAGO 221-415 (5-way)                            | A 5-way WAGO connector securely joins up to 5 wires together. This lets you feed power from one main wire into up to four outgoing wires. We use four of them. Two are the supply buses, one to distribute power and one as a common ground. The other two carry the switched supply out to the three LED strips. The positive one ends up full, the negative one has a way spare                                                                                                                       | 4        | [CPC](https://cpc.farnell.com/wago/221-415/compact-lever-connector-5-way/dp/CN20137)                           |
| WAGO 221-412 (2-way)                            | A 2-way WAGO connector securely joins 2 wires together. Two of them join the speaker leads to the cables from the amplifier, so the speaker can be parted from the board without cutting anything. The third joins the pigtail to the switch lead. Add more if you use them to break up long runs                                                                                                                                                                                                       | 3        | [CPC](https://cpc.farnell.com/wago/221-412/compact-lever-connector-2-way/dp/CN20135)                           |
| Belkin BoostCharge 10K (BPB011)                 | A 10000mAh power bank should give 90hrs of continuous use before needing recharged                                                                                                                                                                                                                                                                                                                                                                                                                      | 1        | [Belkin](https://www.belkin.com/uk/p/power-bank-10k/BPB011btBK.html)                                           |
| Panasonic EEUFR1A102L, 1000 µF 10 V             | When the strips switch on and a beep starts at the same moment, the box asks for about 1.4 A in an instant. The power bank and the cable to it cannot respond that fast, so the 5 V rail dips. A big enough dip resets the Pico. The capacitor sits next to the load with that energy already stored, and supplies the first few milliseconds itself while the bank catches up. 1000 µF is sized for that surge. The 10 V part is headroom. On a 5 V rail you want a capacitor rated at roughly double. | 1        | [CPC](https://cpc.farnell.com/panasonic/eeufr1a102l/capacitor-radial-10v-1000uf/dp/CA07459)                    |
| 1N5817 Schottky                                 | It lets you plug the micro-USB in without the two power sources fighting. You can leave the box switched on and plug in a laptop to reflash firmware.                                                                                                                                                                                                                                                                                                                                                   | 1        | [CPC](https://cpc.farnell.com/taiwan-semiconductor/1n5817/schottky-rectifier-1a-20v-do-204al/dp/SC21533)       |
| Power on/off toggle switch                      |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         | 1        | [The Pi Hut](https://thepihut.com/products/illuminated-toggle-switch-with-cover-red)                           |
| 6.3 mm insulated spade crimps                   | Needed to connect to the toggle switch assuming you buy the type linked to above                                                                                                                                                                                                                                                                                                                                                                                                                        | 3        | [The Pi Hut](https://thepihut.com/products/spade-quick-connector-kit-6-3mm-4-8mm-2-8mm)                        |
| Hookup wire, 16/0.2 mm (0.5 mm², approx 20 AWG) | The thicker of the two. Rated about 3 A, and needed anywhere the full box current flows: the switch to the +5 V bus, the two LED rails, and all three of the MOSFET module's power terminals. Also both wires you crimp spades onto at the switch, because a 6.3 mm spade will not close on anything thinner. Buy two or three colours, the link is one of them                                                                                                                                         |          | [CPC](https://cpc.farnell.com/concordia-technologies/ew16-0-2blu-10m/equipment-wire-16-0-20mm-blue/dp/CB19941) |
| Hookup wire, 7/0.2 mm (0.22 mm², approx 24 AWG) | The thinner of the two. Rated about 1.4 A, which is fine for the signals and for the amplifier feed, but not for the runs above. Also the only one of the two that will fit a Dupont terminal. Again, two or three colours                                                                                                                                                                                                                                                                              |          | [CPC](https://cpc.farnell.com/concordia-technologies/ew7-0-2blk10m/equipment-wire-7-0-20mm-black/dp/CB19933)   |
| Bootlace ferrules and crimper                   | Not strictly necessary but it can make it easier to secure the wire to the screw terminals                                                                                                                                                                                                                                                                                                                                                                                                              |          |                                                                                                                |
| Hammond 1556GAWH ABS box                        | This is the enclosue into which we will mount all the components and keep them out of sight. The outside of the lid will have the led strips.                                                                                                                                                                                                                                                                                                                                                           | 1        | [RS Components](https://uk.rs-online.com/web/p/general-purpose-enclosures/2777586)                             |
| Micro-USB cable                                 | Make sure you get a cable that carries both charge and data. Some only carry charge and you will not be able to flash the firmware.                                                                                                                                                                                                                                                                                                                                                                     | 1        | [The Pi Hut](https://thepihut.com/products/usb-c-to-micro-usb-cable-black)                                     |

## Tools

We have tried to make this as simple as possible to assemble but there is still a need to prepare cables and perform 
some very basic soldering. there are plenty of options on the market. These are just the ones we happen to like.

| Tool           | Description                                                | Link                                                                                                   |
|----------------|------------------------------------------------------------|--------------------------------------------------------------------------------------------------------|
| Engineer PA-09 | Japanese made precisely engineered universal crimping tool | [The Pi Hut](https://thepihut.com/products/universal-micro-crimping-pliers-1-0-to-1-9mm-size-contacts) |
| Engineer PA-14 | Japanese made professional grade wire strippers            | [The Pi Hut](https://thepihut.com/products/engineer-pa-14-pro-wire-strippers-awg20-awg34)              |
| Pinecil V2     | Smart USB-C powered Mini Portable Soldering Iron           | [Test Clips](https://testclips.co.uk/product/pinecil-smart-mini-portable-soldering-iron/)              |

## Wiring
![Wiring Diagram](wiring.svg)

Thirty connections in all: fourteen for power, six for signal and ten for the outputs. Work down the lists and the box is wired.

### Wiring the power bank to the switch

#### USB-A male to bare-wire pigtail 
A USB-A male to bare-wire pigtail is  USB-A male plug with bare wires on the other end. Sold as a "USB power pigtail" 
or "USB-A to open end". These can easily be made by cutting the small end off any cheap USB cable.

A full USB cable has four conductors. Nominally red for +5 V, black for ground, and white and green for data. 
You want only the first two. Cut the data pair back and heatshrink them individually to avoid having bare data wires 
which could short against a terminal.

#### Making the connections
1. Drill a hole in the Hammond 1556GAWH ABS box and mount the switch
2. Crimp three 6.3 mm female insulated spades: pigtail red, a wire to the +5 V WAGO, and a wire to a spare GND terminal on the Pico board. Both of the wires you make up are 16/0.2, because a 6.3 mm spade will not close on anything thinner. Strip 5 to 6 mm, crimp, and tug each one firmly. A good spade takes deliberate force to pull off.
3. Push them on: pigtail red to the supply terminal, the +5 V WAGO wire to the switched output, the ground wire to the LED terminal.
4. Test before going further. Plug the pigtail into the bank, put the meter across the switched output and the pigtail's black wire: 0 V with the switch off, about 5 V with it on, and the switch's own lamp should light. Only now connect anything to the WAGO.
5. Anchor the pigtail with a cable tie base near the switch, so tugging the power bank never pulls on a spade terminal.

### Power connections

Fourteen connections. Work down the list and the power side of the box is wired.

| #   | From                                    | To                                      | Wire             | How                                                                                                                                                              |
|-----|-----------------------------------------|-----------------------------------------|------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| P1  | Power bank USB socket                   | USB-A male pigtail                      | The cable itself | Plug it in. The far end is two bare wires, red and black.                                                                                                        |
| P2  | Pigtail red                             | Switch, + terminal                      | Pigtail's own    | 6.3 mm spade crimp. This is the supply coming in.                                                                                                                |
| P3  | Switch, headlamp terminal               | +5 V WAGO                               | 16/0.2           | Spade at the switch, bare wire into the WAGO. Everything in the box is fed through this one wire, about 1.3 A, so it has to be the thicker one.                  |
| P4  | Switch, ground terminal                 | Pico board, spare GND terminal (pin 3)  | 16/0.2           | Spade at the switch, bare wire into the screw terminal. Only 10 to 20 mA for the lamp, but a 6.3 mm spade will not grip anything thinner.                        |
| P5  | Pigtail black                           | GND WAGO                                | Pigtail's own    | Bare wire into the WAGO.                                                                                                                                         |
| P6  | Capacitor 1000 µF, + leg                | +5 V WAGO                               | Component leg    | The leg goes straight in. No wire, no crimp.                                                                                                                     |
| P7  | Capacitor 1000 µF, − leg (striped side) | GND WAGO                                | Component leg    | Same again. Fitting it the wrong way round destroys the capacitor.                                                                                               |
| P8  | +5 V WAGO                               | Schottky diode, plain leg               | Component leg    | The leg goes straight into the WAGO.                                                                                                                             |
| P9  | Schottky diode, striped leg             | Pico VSYS, physical pin 39              | Component leg    | Straight into the screw terminal. No crimp.                                                                                                                      |
| P10 | GND WAGO                                | Pico GND, physical pin 38               | 7/0.2            | Bare into the WAGO, bare into the GND screw terminal. The Pico draws about 130 mA.                                                                               |
| P11 | +5 V WAGO                               | MAX98357A VIN                           | 7/0.2            | Bare into the WAGO, Dupont onto the pin. Do not use 16/0.2 here, as a Dupont terminal will not close over 0.5 mm². At 0.7 A over 150 mm, 7/0.2 drops only 16 mV. |
| P12 | GND WAGO                                | MAX98357A GND                           | 7/0.2            | Same as P11. The return carries the same current as the feed.                                                                                                    |
| P13 | +5 V WAGO                               | LED + WAGO                              | 16/0.2           | Bare into both. This one wire feeds all three strips and the module's VIN, 0.45 A.                                                                               |
| P14 | GND WAGO                                | MOSFET module GND                       | 16/0.2           | Bare into the WAGO, bare into the screw terminal. The return path for the strips.                                                                                |

#### What goes in each WAGO

These are the two supply buses. The two LED WAGOs are separate and are listed with the output connections.

**+5 V bus, 5-way, all 5 ways used**

1. Switched supply from the switch (P3)
2. Capacitor + leg (P6)
3. Diode leg feeding the Pico (P8)
4. Amplifier VIN (P11)
5. Feed to the LED + WAGO (P13)

**Ground bus, 5-way, all 5 ways used**

1. Pigtail black (P5)
2. Capacitor − leg (P7)
3. Pico GND (P10)
4. Amplifier GND (P12)
5. MOSFET GND (P14)

Low current grounds do not need to come here at all. The switch lamp goes to a spare GND screw terminal on the Pico board instead (P4), which is why ground still fits in one connector.

### Signal connections

Six connections. These carry no real current, so 7/0.2 is used throughout.

| #  | From                   | To                                   | Wire           | How                                                                                                          |
|----|------------------------|--------------------------------------|----------------|--------------------------------------------------------------------------------------------------------------|
| S1 | Pico GP16 (pin 21)     | MAX98357A BCLK                       | 7/0.2          | Screw terminal at the Pico, Dupont at the amplifier.                                                         |
| S2 | Pico GP17 (pin 22)     | MAX98357A LRC                        | 7/0.2          | Same as S1.                                                                                                  |
| S3 | Pico GP18 (pin 24)     | MAX98357A DIN                        | 7/0.2          | Same as S1.                                                                                                  |
| S4 | Pico GP22 (pin 29)     | MOSFET module signal (green or blue) | Supplied cable | Use the module's own 3-pin Gravity cable. Cut the housing off the far end, see below.                        |
| S5 | Pico 3V3(OUT) (pin 36) | MOSFET module VCC (red)              | Supplied cable | Same cable. Take this from the Pico's 3.3 V output, not from the 5 V bus.                                    |
| S6 | Pico GND (pin 28)      | MOSFET module logic GND (black)      | Supplied cable | Same cable. Not optional. This is the return for the module's own logic supply, nothing switches without it. |

#### The Gravity cable

S4, S5 and S6 are all one cable, not three separate wires. The MOSFET module comes with a 3-pin Gravity lead. Leave the PH2.0 plug on the module end, as it is a proper latching connector and worth keeping.

The other end will not plug into anything. It carries a 3-way Dupont housing, and the three pins are not in a row. 3V3(OUT) exists only at pin 36, and its neighbours are ADC_VREF, 3V3_EN and a ground that is already taken, so no run of three adjacent pins will give you a signal, 3.3 V and a ground. The Pico end of this build is screw terminals in any case.

So cut the housing off, strip the three wires, optionally fit a ferrule to each and screw them in by colour:

1. Green or blue is the signal, to GP22 (pin 29)
2. Black is ground, to GND (pin 28)
3. Red is VCC, to 3V3(OUT) (pin 36)

The first two are adjacent terminals. The red wire runs about seven terminals along to pin 36.

GP22 is the nearest pin to 3V3(OUT) with no second job. GP26, GP27 and GP28 are closer, but they are the only three analogue capable pins on the board and there is no reason to spend one on a digital output.

Count carefully at both ends. Pin 30, right next to GP22, is RUN, and a wire in there holds the Pico in reset. Pin 35, right next to 3V3(OUT), is ADC_VREF.


#### Pico pins used

Worth checking against your board before you start, so nothing clashes.

| Pin | Name     | Used by                            |
|-----|----------|------------------------------------|
| 3   | GND      | Switch lamp (P4)                   |
| 21  | GP16     | Amplifier BCLK (S1)                |
| 22  | GP17     | Amplifier LRC (S2)                 |
| 24  | GP18     | Amplifier DIN (S3)                 |
| 28  | GND      | MOSFET module ground (S6)          |
| 29  | GP22     | MOSFET module signal (S4)          |
| 36  | 3V3(OUT) | MOSFET module VCC (S5)             |
| 38  | GND      | Main ground from the GND bus (P10) |
| 39  | VSYS     | Main supply through the diode (P9) |

Pin 3 is a plain ground and sits near the switch. Pin 8 does the job just as well if that suits your layout better. Do not use pin 33. That one is the analogue ground, and lamp current has no business there.

### Output connections

Ten connections. This is everything that leaves the box: the speaker and the three LED strips.

| #   | From                | To                       | Wire          | How                                                                                                                                      |
|-----|---------------------|--------------------------|---------------|------------------------------------------------------------------------------------------------------------------------------------------|
| O1  | MAX98357A speaker + | 2-way WAGO, then speaker | Speaker's own | Strip 6 mm, into the 3.5 mm screw terminal, tighten. If you need to extend, use 16/0.2. This pair carries close to 0.9 A at full output. |
| O2  | MAX98357A speaker − | Same again, other pole   | Speaker's own | Polarity does not matter with a single speaker. Swapping the pair only inverts the waveform.                                             |
| O3  | LED + WAGO          | MOSFET VIN               | 16/0.2        | Bare into the WAGO, bare into the screw terminal. Carries almost no current, but without it the module cannot switch at all.             |
| O4  | MOSFET VOUT         | LED − WAGO               | 16/0.2        | Bare into the screw terminal, bare into the WAGO. This is the switched side and carries the full 0.45 A.                                 |
| O5  | LED + WAGO          | Strip 1, + pad           | 16/0.2        | Solder to the pad, sleeve the joint in heatshrink.                                                                                       |
| O6  | LED − WAGO          | Strip 1, − pad           | 16/0.2        | Same as O5.                                                                                                                              |
| O7  | LED + WAGO          | Strip 2, + pad           | 16/0.2        | Same as O5.                                                                                                                              |
| O8  | LED − WAGO          | Strip 2, − pad           | 16/0.2        | Same as O5.                                                                                                                              |
| O9  | LED + WAGO          | Strip 3, + pad           | 16/0.2        | Same as O5.                                                                                                                              |
| O10 | LED − WAGO          | Strip 3, − pad           | 16/0.2        | Same as O5.                                                                                                                              |

#### The three strips run in parallel

Each strip is 150 mm, and each one gets its own pair of wires back to the box. Nothing joins one strip to the next.

#### How the module is actually wired

The module does not have a pair of output terminals. Its power side has three, and they are marked VIN, GND and VOUT.

- **VIN** is the positive rail coming in. It also feeds the gate drive, so it must be connected or the MOSFET can never turn on. It carries almost no current itself.
- **GND** is the negative rail going back to the power bank.
- **VOUT** is the switched terminal. The MOSFET sits between VOUT and GND, and that is the only break in the circuit.

So the strips do not hang across a pair of outputs. They hang between the positive rail and VOUT. Their positives sit in the same connector as VIN because they are the same rail, and their negatives go to VOUT.

Follow the current round once and it is obvious. Out of the +5 V bus, into the LED + WAGO, out to a strip, through its LEDs, back on its negative, into the LED − WAGO, into VOUT, through the MOSFET, out of GND, into the GND WAGO, home to the power bank.

#### The two LED WAGOs

These are separate from the two supply buses and must not be confused with them.

**LED + WAGO, 5-way, all 5 used**

1. Feed from the +5 V bus (P13)
2. To MOSFET VIN (O3)
3. Strip 1 positive (O5)
4. Strip 2 positive (O7)
5. Strip 3 positive (O9)

**LED − WAGO, 5-way, 4 ways used**

1. To MOSFET VOUT (O4)
2. Strip 1 negative (O6)
3. Strip 2 negative (O8)
4. Strip 3 negative (O10)

The LED − WAGO is not a ground. It only sits near 0 V while the strips are lit. Never join it to the GND WAGO. If a strip negative reaches ground by any other route it skips the MOSFET entirely, and that strip lights the moment you flip the switch and never flashes.

WAGO do not make a 4-way in this range, so both of these are 221-415. The positive one is full. The spare way on the negative one is handy for a meter probe, but it will not get you a fourth strip, because a fourth strip needs a hole on both rails.

#### Solder the strip leads, do not use clips

Solderless clips are the least reliable part of any strip build, and yours will be on the outside of the box where a bad one is obvious. Each strip now needs only one connection, so solder the pair directly to its pads and sleeve each joint in heatshrink.

#### Watch the polarity

The strip prints + and − along its length. Check the marking before you solder, on all three. The speaker pair (O1 and O2) is the only place in the whole build where polarity does not matter.

#### The lid split

The 2-way WAGO on the speaker pair lets you lift the lid off without unsoldering anything. Put it close to the split so both halves have enough slack to sit apart on the bench.
