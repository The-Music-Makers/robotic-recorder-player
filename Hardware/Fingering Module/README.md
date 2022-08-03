
# Fingering Module


<p float="left">
  <img src="../../Documents/fingering_module_assembly_overview_with_frame.png" height="500" />
</p>

## Bill of Materials

The robot recorder player relies on readily available hobby electronics components in the spirit of the CERN-OHL-W. The components can be changed for other makes or types but changing the components will have an effect on how each module operates, for some types of woodwind instruments changes may be needed to allow the modules to operate as desired. Links have been provided for UK suppliers for the components used to create the module, these suppliers are not the only source of the components and they can be bought from other suppliers or locations.

### Purchase
| Item | Quantity | Details | Example |
| - | - | - | - |
| Arduino Mega | 1 | | [UK](https://www.amazon.co.uk/ELEGOO-Controller-ATmega2560-ATMEGA16U2-Compatible/dp/B06XKMZ3T9/)|
| Power Supply | 1 | ~~12V, 10A~~ [^voltage] | [UK](https://www.amazon.co.uk/SHNITPWR-100V-240V-Converter-Transformer-5-5x2-5mm/dp/B08BJRN5SX/)|
| Solenoid | 10 | Model: JF-0530B, 12V | [UK](https://www.amazon.co.uk/Rtengtunn-JF-0530B-Push-Pull-Gangbei-0530B-Electromagnet/dp/B08291L2XL/)|
| TIP120 Darlington Transistor | 10 | | [UK](https://www.amazon.co.uk/BOJACK-Epitaxial-Transistor-Darlington-Transistors/dp/B08D8SJPCG/ref=sr_1_4?dchild=1&keywords=TIP120+Darlington+Transistor&qid=1614263478&sr=8-4)|
| 1K Ohm Resistor | 10 | | [UK](https://www.amazon.co.uk/sourcing-map-Metal-Resistors-Tolerances/dp/B07LGM23Y4/ref=sr_1_10?dchild=1&keywords=1K+Ohm+Resistor&qid=1614263525&sr=8-10)|
| 1N4001 Diode | 10 | | [UK](https://www.amazon.co.uk/ExcLent-100Pcs-1N4001-50V-Diode/dp/B07J3ZT55G/ref=sr_1_8?dchild=1&keywords=1N4001+Diode&qid=1614263550&sr=8-8)|
| Stripboard[^breadboard], wires, connectors | | Stipboard or perfboard depending on preference | |
| Pan head wood screw | 22 | 12 mm x 3.5 mm | [UK](https://www.toolstation.com/self-tapping-pan-head-pozi-screw/p74035) |
| M3 x 25 mm bolt and nut | 4 | | [UK](https://www.amazon.co.uk/Screw-Bolts-Stainless-Steel-340pcs/dp/B08RRW6B3H/ref=sr_1_12?dchild=1&keywords=M3+nut+and+bolt&qid=1614263398&sr=8-12)|
| Board (plywood or breadboard) | 1 | 350 x 250 x 15 mm | |

[^voltage]: If the solenoids are run continuously at 12V they will overheat. Currently the system is being run at 8V but we intend to implement a PWM solution so 12V can be used for initial actuation then 8V for a holding current.

[^breadboard]: Note, a breadboard cannot be used here as it won't handle the current.

### Make
| Item | Quantity | Method | Model |
| - | - | - | - |
| Holder Foot End | 1 | 3D Print | [`holder_foot.3mf`](holder_foot.3mf) |
| Holder Head End | 1 | 3D Print | [`holder_head.3mf`](holder_head.3mf) |
| Five Finger Box | 1 | 3D Print | [`finger-box_five.3mf`](finger-box_five.3mf) |
| Thumb Finger Box | 1 | 3D Print | [`finger-box_thumb.3mf`](finger-box_thumb.3mf) |
| Double Tone Hole Finger Box | 1 | 3D Print | [`finger-box_double-hole.3mf`](finger-box_double-hole.3mf) |
| Stand | 1 | 3D Print | [`stand.3mf`](stand.3mf) |

All of these parts were printed in PLA. 0.4 mm nozzle, 0.2 mm layer height, 2 walls, 20% infill are adequate settings. Supports aren't required if they are printed in the correct orientation. The files are supplied in 3MF format (see issue https://github.com/The-Music-Makers/music_makers/issues/45) which mainstream slicers will load.

### Fingertips
It is necessary to put a soft material on the end of the solenoid plungers to protect the recorder and ensure an adequate seal. They are still in the experimental stage and details of our attempts and ideas are below.

1. **Foam ear plugs.** A hole can be made in the end and they can be glued to the plunger.
2. **3D Printed Flexible Filament.** Print the following parts in a flexible filament.
    | Item | Quantity | Model |
    | - | - | - |
    | Main fingertip | 6 | [`finger-tip_main.3mf`](finger-tip_main.3mf)|
    | Double tone hole large fingertip | 2 | [`finger-tip_double-big.3mf`](finger-tip_double-big.3mf)|
    | Double tone hole small fingertip | 2 | [`finger-tip_double-small.3mf`](finger-tip_double-small.3mf)|

    We used TPU with a shore hardness of 95A. They were printed in vase mode but with 3 mm of bottom layers. This results in a solid bottom which will screw onto the plunger and a hollow top which will deform to the tone holes.
3. **Casting silicone.** We would like to try casting silicone fingertips.


## Assembly Instructions
1. Obtain and make all the parts listed above.
1. Attach the head and foot holder to the board with pan head screws, insert the recorder and use the M3 bolts and nuts to secure.
1. Insert the solenoids into the finger boxes and secure with a pan head screw if loose.
1. Attach fingertips to the solenoid plungers.
1. Line up the finger boxes to the recorder and attach to the board with pan head screws.
1. The solenoids need to be connected to the power supply and Arduino (plus the resistor, diode and transistor) as per the following diagram. <p><img float="left" src="../../Documents/singleSolenoidWiringDiagram.PNG" height="300"/></p> We drilled holes in the board to pass the solenoid wires through and connected everything on stripboard. Each solenoid circuit as per the image needs to be connected to a different output pin of the Arduino, noting the pin number.