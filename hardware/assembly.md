# Raijin Assembly

Here we detail all of the materials needed to construct the device, how to assemble and the tools you will need. 
At the time of writing you can expect to pay approximately £150 for all the parts and a further £150 for the tools.

## Bill of Materials

| Item                                                 | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               | Quantity | Link                                                                                                                                 |
|------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------|--------------------------------------------------------------------------------------------------------------------------------------|
| Raspberry Pi Pico 2 W, headers fitted                | Easiest to purchase the version with the headers fitted as we will be mounting this onto a breakout board.                                                                                                                                                                                                                                                                                                                                                                                                | 1        | [The Pi Hut](https://thepihut.com/products/raspberry-pi-pico-2-w?variant=54063378760065)                                             |
| Freenove FNK0081 Breakout Board for Pico             | There are many breakout boards to choose from but this one gave the best documentation                                                                                                                                                                                                                                                                                                                                                                                                                    | 1        | [Freenove Store](https://store.freenove.com/products/fnk0081)                                                                        |
| Adafruit ADA3006 MAX98357A amplifier                 |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           | 1        | [The Pi Hut](https://thepihut.com/products/adafruit-i2s-3w-class-d-amplifier-breakout-max98357a)                                     |
| Speaker, 4 Ω 3 W, flying leads                       | The speaker will connect to the amplifier via a WAGO connector so be sure to get a speaker with cables that have bare ends                                                                                                                                                                                                                                                                                                                                                                                | 1        | [The Pi Hut](https://thepihut.com/products/mono-enclosed-speaker-with-plain-wires-3w-4-ohm)                                          |
| Adafruit MOSFET Driver, ADA5648                      | The Pico has the control logic but it is this board which does the switching, all three strips together on one channel. Fully assembled, so there is nothing to solder onto it: a STEMMA JST PH socket takes power and signal, and two latching terminal blocks take the strips. Its gate is driven straight from the GPIO, so a 3.3 V output switches it fully and there is no logic supply to wire. Rated 1.5 A continuous against the 0.45 A the strips draw                                           | 1        | [The Pi Hut](https://thepihut.com/products/adafruit-mosfet-driver-for-motors-solenoids-leds-etc-stemma-jst-ph-2mm)                   |
| STEMMA JST PH 3-pin to male header cable, ADA3893    | Carries V+, GND and the GP22 signal to the MOSFET driver, and is not supplied with it. The three wires end in individual male header pins, which is the point: a pin is thick enough for a WAGO to clamp, where the bare 26 AWG conductor sits below the connector's 0.14 mm² minimum and pulls straight back out                                                                                                                                                                                         | 1        | [The Pi Hut](https://thepihut.com/products/stemma-jst-ph-3-pin-to-male-header-cable-200mm)                                           |
| PAUTIX 5 V COB strip, 2 m                            | We cut this into three 150 mm strips that sit side by side on the enclosure lid. The strip cuts every 12.5 mm, so 150 mm lands exactly on a mark. That uses 450 mm of the 2 m reel and leaves plenty spare for mistakes. The whole reel wants 5 V at 2 A, so about 1 A per metre, which puts the three strips together at 0.45 A. That is the figure used throughout the wiring tables.                                                                                                                   | 1        | [Amazon](https://www.amazon.co.uk/dp/B08XBW48K9?th=1)                                                                                |
| USB-A male to bare-wire pigtail                      | In theory you can cut the end off a spare USB A cable you may have to hand but not all cables have just red and black so you are probably better off buying one                                                                                                                                                                                                                                                                                                                                           | 1        | [Amazon](https://www.amazon.co.uk/dp/B0CWNQB19C)                                                                                     |
| WAGO 221-415 (5-way)                                 | A 5-way WAGO connector securely joins up to 5 wires together. This lets you feed power from one main wire into up to four outgoing wires. We use two of them as the supply buses, one to distribute power and one as a common ground. Both end up full. The LED strips need none: one pair of wires runs from the MOSFET driver to strip 1, and short links carry it on to strips 2 and 3                                                                                                                 | 2        | [CPC](https://cpc.farnell.com/wago/221-415/compact-lever-connector-5-way/dp/CN20137)                                                 |
| WAGO 221-412 (2-way)                                 | A 2-way WAGO connector securely joins 2 wires together. Two of them join the speaker leads to the cables from the amplifier, so the speaker can be parted from the board without cutting anything. The third joins the pigtail to the switch lead. Add more if you use them to break up long runs                                                                                                                                                                                                         | 3        | [CPC](https://cpc.farnell.com/wago/221-412/compact-lever-connector-2-way/dp/CN20135)                                                 |
| Belkin BoostCharge 10K (BPB011)                      | A 10000mAh power bank should give 90hrs of continuous use before needing recharged                                                                                                                                                                                                                                                                                                                                                                                                                        | 1        | [Belkin](https://www.belkin.com/uk/p/power-bank-10k/BPB011btBK.html)                                                                 |
| Panasonic EEUFR1A102L, 1000 µF 10 V                  | When the strips switch on and a beep starts at the same moment, the box asks for about 1.4 A in an instant. The power bank and the cable to it cannot respond that fast, so the 5 V rail dips. A big enough dip resets the Pico. The capacitor sits next to the load with that energy already stored, and supplies the first few milliseconds itself while the bank catches up. 1000 µF is sized for that surge. The 10 V part is headroom. On a 5 V rail you want a capacitor rated at roughly double.   | 1        | [CPC](https://cpc.farnell.com/panasonic/eeufr1a102l/capacitor-radial-10v-1000uf/dp/CA07459)                                          |
| 1N5817 Schottky                                      | It lets you plug the micro-USB in without the two power sources fighting. You can leave the box switched on and plug in a laptop to reflash firmware.                                                                                                                                                                                                                                                                                                                                                     | 1        | [CPC](https://cpc.farnell.com/taiwan-semiconductor/1n5817/schottky-rectifier-1a-20v-do-204al/dp/SC21533)                             |
| On-Off Latching 12mm Flat Push Button Switch         |                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           | 1        | [Switch Electronics](https://www.switchelectronics.co.uk/products/on-off-latching-12mm-flat-push-button-switch-stainless-steel-ip65) |
| Hookup wire, 16/0.2 mm (0.5 mm², approx 20 AWG)      | The thicker of the two. Rated about 3 A, and needed anywhere the full box current flows: the switch to the +5 V bus, and the pair from the MOSFET driver out to strip 1, which carries the whole 0.45 A for all three strips. The links onward to strips 2 and 3 carry less but use the same wire, and the extra size makes for a sturdier joint at the pads. Also both wires you crimp spades onto at the switch or you can solder direct tot he lugs. Buy two or three colours, the link is one of them |          | [CPC](https://cpc.farnell.com/concordia-technologies/ew16-0-2blu-10m/equipment-wire-16-0-20mm-blue/dp/CB19941)                       |
| Hookup wire, 7/0.2 mm (0.22 mm², approx 24 AWG)      | The thinner of the two. Rated about 1.4 A, which is fine for the signals and for the amplifier feed, but not for the runs above. Also the only one of the two that will fit a Dupont terminal. Again, two or three colours                                                                                                                                                                                                                                                                                |          | [CPC](https://cpc.farnell.com/concordia-technologies/ew7-0-2blk10m/equipment-wire-7-0-20mm-black/dp/CB19933)                         |
| Bootlace ferrules and crimper                        | Not strictly necessary but it can make it easier to secure the wire to the screw terminals                                                                                                                                                                                                                                                                                                                                                                                                                |          |                                                                                                                                      |
| Hammond 1556GAWH ABS box                             | This is the enclosure into which we will mount all the components and keep them out of sight. The outside of the lid will have the led strips.                                                                                                                                                                                                                                                                                                                                                            | 1        | [RS Components](https://uk.rs-online.com/web/p/general-purpose-enclosures/2777586)                                                   |
| Micro-USB cable                                      | Make sure you get a cable that carries both charge and data. Some only carry charge and you will not be able to flash the firmware.                                                                                                                                                                                                                                                                                                                                                                       | 1        | [The Pi Hut](https://thepihut.com/products/usb-c-to-micro-usb-cable-black)                                                           |
| Adafruit ADA6068 micro-B panel mount extension cable | The firmware port. Micro-B socket outside, micro-B plug inside, straight into the Pico. Needs a round hole between 12 mm and 18 mm, so the step drill covers it. Once the box is closed this is the only way to reflash, as the BOOTSEL button is sealed inside, so test that it carries data before you drill anything                                                                                                                                                                                   | 1        | [The Pi Hut](https://thepihut.com/products/usb-micro-b-small-round-panel-mount-extension-usb-cable)                                  |
| Adafruit ADA4218 USB-C panel mount extension cable   | The charging port, so the power bank can be topped up without opening the box. USB-C socket outside, USB-C plug inside for the bank. Needs a round hole of about 22 mm.                                                                                                                                                                                                                                                                                                                                   | 1        | [The Pi Hut](https://thepihut.com/products/usb-c-round-panel-mount-extension-cable-30cm)                                             |
| Extra Strong Foam Mounting Tape 25mm x 10m           | Used to mount the speaker to the inside of the lid and to secure the various WAGO connectors in position                                                                                                                                                                                                                                                                                                                                                                                                  | 1        | [ToolStation](https://www.toolstation.com/extra-strong-foam-mounting-tape/p45669)                                                    |
| VELCRO Brand Heavy Duty Stick On Strips 50mm x 100mm | Used to mount the power bank to the inside of the lid. Using velcro allows the power bank to be replaced.                                                                                                                                                                                                                                                                                                                                                                                                 | 1        | [ToolStation](https://www.toolstation.com/velcro-brand-heavy-duty-stick-on-strips/p62488)                                            |

## Tools

We have tried to make this as simple as possible to assemble but there is still a need to prepare cables and perform 
some very basic soldering. There are plenty of options on the market. These are just the ones we happen to like.

| Tool                                  | Description                                                         | Link                                                                                                   |
|---------------------------------------|---------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------|
| Engineer PA-09                        | Japanese made precisely engineered universal crimping tool          | [The Pi Hut](https://thepihut.com/products/universal-micro-crimping-pliers-1-0-to-1-9mm-size-contacts) |
| Engineer PA-14                        | Japanese made professional grade wire strippers                     | [The Pi Hut](https://thepihut.com/products/engineer-pa-14-pro-wire-strippers-awg20-awg34)              |
| Pinecil V2                            | Smart USB-C powered Mini Portable Soldering Iron                    | [Test Clips](https://testclips.co.uk/product/pinecil-smart-mini-portable-soldering-iron/)              |
| Titanium Coated Step Drill Bit 4-22mm | A step drill bit is ideal to cut holes in the ABS plastic enclosure | [ToolStation](https://www.toolstation.com/titanium-coated-step-drill-bit/p78333)                       |

## Wiring
![Wiring Diagram](wiring.svg)

Twenty-five connections in all: thirteen for power, four for signal and eight for the outputs. Work down the lists and the box is wired.

### Wiring the power bank to the switch

#### USB-A male to bare-wire pigtail 
A USB-A male to bare-wire pigtail is  USB-A male plug with bare wires on the other end. Sold as a "USB power pigtail" 
or "USB-A to open end". These can easily be made by cutting the small end off any cheap USB cable.

A full USB cable has four conductors. Nominally red for +5 V, black for ground, and white and green for data. 
You want only the first two. Cut the data pair back and heatshrink them individually to avoid having bare data wires 
which could short against a terminal.

#### Making the connections

The switch interrupts the positive line and nothing else. The pigtail's black wire never goes near it.

1. Drill a 12 mm round hole in the Hammond 1556GAWH ABS box and mount the switch. Check the clearance behind the panel first: the body is 25.95 mm deep and 13.8 mm across, and it will be competing with the power bank and the Pico board for room.
2. The switch is SPST with two 2.8 mm tabs, and both tabs are ends of the same normally-open contact. There is no polarity and no right way round. Either tab takes either wire.
3. Solder 16/0.2 to each tab and sleeve each joint in heatshrink, or crimp 2.8 mm spades if you would rather. The tabs are made for both, and soldering avoids the question of whether your crimper handles that size.
4. One tab joins the pigtail's red wire. The other runs to the +5 V WAGO, carrying about 1.3 A, which is why it is the thicker wire. The pigtail's black wire goes straight to the GND WAGO.
5. Test before going further. Plug the pigtail into the bank, put the meter between the switch's outgoing wire and the pigtail's black wire: 0 V with the switch out, about 5 V with it pushed in. Only now connect anything to the WAGO.
6. Anchor the pigtail with a cable tie base near the switch, so tugging the power bank never pulls on a tab.

The switch has no lamp, so nothing on the outside of the box tells you it is on until a clip plays up to thirty seconds later.

### Power connections

Thirteen connections. Work down the list and the power side of the box is wired.

| #   | From                                    | To                                      | Wire             | How                                                                                                                                                              |
|-----|-----------------------------------------|-----------------------------------------|------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| P1  | Power bank USB socket                   | USB-A male pigtail                      | The cable itself | Plug it in. The far end is two bare wires, red and black.                                                                                                        |
| P2  | Pigtail red                             | Switch, either tab                      | Pigtail's own    | Soldered to the 2.8 mm tab, or a 2.8 mm spade crimp. This is the supply coming in.                                                                               |
| P3  | Switch, other tab                       | +5 V WAGO                               | 16/0.2           | Soldered at the switch, bare wire into the WAGO. Everything in the box is fed through this one wire, about 1.3 A, so it has to be the thicker one.               |
| P4  | Pigtail black                           | GND WAGO                                | Pigtail's own    | Bare wire into the WAGO.                                                                                                                                         |
| P5  | Capacitor 1000 µF, + leg                | +5 V WAGO                               | Component leg    | The leg goes straight in. No wire, no crimp.                                                                                                                     |
| P6  | Capacitor 1000 µF, − leg (striped side) | GND WAGO                                | Component leg    | Same again. Fitting it the wrong way round destroys the capacitor.                                                                                               |
| P7  | +5 V WAGO                               | Schottky diode, plain leg               | Component leg    | The leg goes straight into the WAGO.                                                                                                                             |
| P8  | Schottky diode, striped leg             | Pico VSYS, physical pin 39              | Component leg    | Straight into the screw terminal. No crimp.                                                                                                                      |
| P9 | GND WAGO                                | Pico GND, physical pin 38               | 7/0.2            | Bare into the WAGO, bare into the GND screw terminal. The Pico draws about 130 mA.                                                                               |
| P10 | +5 V WAGO                               | MAX98357A VIN                           | 7/0.2            | Bare into the WAGO, Dupont onto the pin. Do not use 16/0.2 here, as a Dupont terminal will not close over 0.5 mm². At 0.7 A over 150 mm, 7/0.2 drops only 16 mV. |
| P11 | GND WAGO                                | MAX98357A GND                           | 7/0.2            | Same as P10. The return carries the same current as the feed.                                                                                                    |
| P12 | +5 V WAGO                               | MOSFET driver V+ (STEMMA cable, red)    | Cable's own      | Male pin straight into the WAGO. Feeds all three strips, 0.45 A. See the STEMMA cable note below.                                                                |
| P13 | GND WAGO                                | MOSFET driver GND (STEMMA cable, black) | Cable's own      | Male pin straight into the WAGO. The return path for the strips.                                                                                                 |

#### What goes in each WAGO

These are the two supply buses. The two LED WAGOs are separate and are listed with the output connections.

**+5 V bus, 5-way, all 5 ways used**

1. Switched supply from the switch (P3)
2. Capacitor + leg (P5)
3. Diode leg feeding the Pico (P7)
4. Amplifier VIN (P10)
5. MOSFET driver V+ (P12)

**Ground bus, 5-way, all 5 ways used**

1. Pigtail black (P4)
2. Capacitor − leg (P6)
3. Pico GND (P9)
4. Amplifier GND (P11)
5. MOSFET driver GND (P13)

Both buses end up exactly full, and nothing else in the box needs a way. The switch has no lamp to feed, and the MOSFET driver takes its ground through the GND WAGO on its own cable rather than a separate wire from the Pico. If you ever need a sixth connection on either bus, join a second WAGO to the first with a short link rather than trying to double a wire into one hole.

### Signal connections

Four connections. These carry no real current, so 7/0.2 is used where a wire is needed.

| #  | From               | To                      | Wire  | How                                                                                         |
|----|--------------------|-------------------------|-------|---------------------------------------------------------------------------------------------|
| S1 | Pico GP16 (pin 21) | MAX98357A BCLK          | 7/0.2 | Screw terminal at the Pico, Dupont at the amplifier.                                        |
| S2 | Pico GP17 (pin 22) | MAX98357A LRC           | 7/0.2 | Same as S1.                                                                                 |
| S3 | Pico GP18 (pin 24) | MAX98357A DIN           | 7/0.2 | Same as S1.                                                                                 |
| S4 | Pico GP22 (pin 29) | MOSFET driver In        | Cable's own | The STEMMA cable's signal wire. Clip its male pin off, strip the end, screw it into the terminal. See below. |

#### The STEMMA cable

P12, P13 and S4 are all one cable, not three separate wires. The driver has a 3-pin JST PH socket carrying V+, GND and In, and the Adafruit lead plugs into it. There is nothing else to connect on the board's input side, and no logic supply, because the gate is driven straight from the signal wire.

At the far end the three wires finish in individual male header pins. Two of them go into the supply WAGOs exactly as they are. That is the reason for choosing this cable: the pin is about 0.64 mm square, which a WAGO clamps without complaint, whereas the bare 26 AWG conductor is below the connector's 0.14 mm² minimum and works its way out.

The third wire is the signal. Clip its pin off, strip the end and screw it into the GP22 terminal at pin 29.

Check the colours against the driver's silkscreen before powering up. Adafruit's convention is black for ground, red for V+ and white for signal, but neither their page nor The Pi Hut's states it outright.

The driver needs no separate ground wire back to the Pico. Its GND sits in the GND WAGO, which reaches the Pico's ground through P9, so the signal already has a valid reference.

GP22 is the free digital pin nearest that corner. GP26, GP27 and GP28 are closer, but they are the only three analogue capable pins on the board and there is no reason to spend one on a digital output.

Count carefully. Pin 30, right next to GP22, is RUN, and a wire in there holds the Pico in reset.


#### Pico pins used

Worth checking against your board before you start, so nothing clashes.

| Pin | Name     | Used by                            |
|-----|----------|------------------------------------|
| 21  | GP16     | Amplifier BCLK (S1)                |
| 22  | GP17     | Amplifier LRC (S2)                 |
| 24  | GP18     | Amplifier DIN (S3)                 |
| 29  | GP22     | MOSFET driver In (S4)              |
| 38  | GND      | Main ground from the GND bus (P9)  |
| 39  | VSYS     | Main supply through the diode (P8) |

The switch no longer takes a Pico pin. The old illuminated toggle needed a ground for its lamp, which used to sit on pin 3; a plain SPST push button has only its two tabs and nothing to reference.

### Output connections

Eight connections. This is everything that leaves the box: the speaker and the three LED strips.

| #   | From                  | To                       | Wire          | How                                                                                                                                      |
|-----|-----------------------|--------------------------|---------------|------------------------------------------------------------------------------------------------------------------------------------------|
| O1  | MAX98357A speaker +   | 2-way WAGO, then speaker | Speaker's own | Strip 6 mm, into the 3.5 mm screw terminal, tighten. If you need to extend, use 16/0.2. This pair carries close to 0.9 A at full output. |
| O2  | MAX98357A speaker −   | Same again, other pole   | Speaker's own | Polarity does not matter with a single speaker. Swapping the pair only inverts the waveform.                                             |
| O3  | MOSFET driver, **+** terminal | Strip 1, + pad   | 16/0.2        | Press the terminal latch, insert, release, then tug it. Solder the far end to the pad and sleeve the joint. Carries the full 0.45 A.     |
| O4  | MOSFET driver, **−** terminal | Strip 1, − pad   | 16/0.2        | Same as O3. This is the switched side.                                                                                                   |
| O5  | Strip 1, + pad        | Strip 2, + pad           | 16/0.2        | Short link between strips. Solder both ends, sleeve both joints.                                                                         |
| O6  | Strip 1, − pad        | Strip 2, − pad           | 16/0.2        | Same as O5.                                                                                                                              |
| O7  | Strip 2, + pad        | Strip 3, + pad           | 16/0.2        | Same as O5.                                                                                                                              |
| O8  | Strip 2, − pad        | Strip 3, − pad           | 16/0.2        | Same as O5.                                                                                                                              |

#### The strips are chained, and run in parallel

One pair of wires leaves the driver and lands on strip 1. Short links then carry + and − along to strip 2, and again to strip 3. Each strip is simply an extension of the one before it.

Chained is not the same as in series. Every strip sees the same 5 V, because + joins + and − joins −. Wiring them in true series would put about 1.7 V across each and none of them would light.

Strip 1's pads carry the whole 0.45 A, because strips 2 and 3 draw through them. That is well inside 16/0.2, but it does make strip 1's two joints the ones worth getting right.

Only one pair of wires now leaves the box for the LEDs, which is why the two LED WAGOs this build used to need have gone.

#### Lay the strips head to tail

The three sit side by side on the lid, but each one runs in the **opposite direction** to its neighbour. Strip 1 runs one way, strip 2 back the other, strip 3 the same way as strip 1.

That is not cosmetic. Laying them head to tail puts the end you are joining from right next to the end you are joining to, so every link is a short hop across the gap. Run all three the same way and you have to carry each link the full 150 mm length of a strip to reach the next one's input end.

Strip 1 is fed at its free end, links to strip 2 at the other, strip 2 links to strip 3 back at the first end, and strip 3's remaining end is left unconnected.

**The catch.** Because each strip is turned round relative to its neighbour, the + and − pads do not line up across the gap. The + pad of one faces the − pad of the other, so the two link wires cross. That is correct and expected. Go by the printed markings on each strip, never by which side the pad happens to sit on.

#### How the driver is wired

The board has four connections in total, reachable three different ways.

- The **JST PH socket** carries V+, GND and In. That is where the STEMMA cable goes.
- The **two terminal blocks** are the output. One is marked **+** and is joined internally to V+. The other is marked **−** and is the MOSFET's drain, switched to ground whenever In is high. The strips go across the pair.
- A row of **through holes** breaks out the same four nets again, for soldering rather than plugging. Unused in this build.

So it is a low side switch: the MOSFET sits between the **−** terminal and ground, and that is the only break in the circuit. Nothing switches on the positive side.

Follow the current round once and it is obvious. Out of the +5 V bus, along the cable's red wire into V+, across to the **+** terminal, out to strip 1 and on through strips 2 and 3, back on their negatives to the **−** terminal, through the MOSFET, out along the cable's black wire into the GND WAGO, home to the power bank.

#### The terminal blocks are latched, not screwed

Press the latch down with a fingernail or a small flathead screwdriver, insert the wire while the latch is held down, then release. Pull on the wire afterwards and it should not move. To take one out, press the latch again and pull.

Do not force a wire in without pressing the latch. Adafruit warn that the tabs break under too much force.

#### A strip negative is not a ground

The strip negatives go to the driver's **−** terminal and nowhere else. They only sit near 0 V while the strips are lit. Never put one in the GND WAGO. If a strip negative reaches ground by any other route it skips the MOSFET entirely, and the strips light the moment you flip the switch and never flash.

#### Solder the strip leads, do not use clips

Solderless clips are the least reliable part of any strip build, and yours will be on the outside of the box where a bad one is obvious. Solder every strip joint directly to its pads and sleeve each one in heatshrink. Strip 1 takes two wires on each pad, the feed from the driver and the link onward, so tin the pad first and make it one clean joint rather than two stacked ones.

#### Watch the polarity

The strip prints + and − along its length. Check the marking before you solder, on all three, and check it again at every joint.

This matters more here than in most builds, because the head to tail layout turns each strip round relative to its neighbour. The pads do not line up, the link wires cross, and the side a pad sits on tells you nothing. Only the printing does. Get one link the wrong way round and you short the driver's output straight across the supply.

The speaker pair (O1 and O2) is the only place in the whole build where polarity does not matter.

#### The lid split

The 2-way WAGO on the speaker pair lets you lift the lid off without unsoldering anything. Put it close to the split so both halves have enough slack to sit apart on the bench.
