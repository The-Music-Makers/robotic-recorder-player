
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
| Stripboard, wires, connectors | | here[^breadboard]| |
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

All of these parts were printed in PLA. 0.4 mm nozzle, 0.2 mm layer height, 2 walls, 20% infill are adequate settings. Supports aren't required if they are printed in the correct orientation. The files are supplied in 3MF format (https://github.com/The-Music-Makers/music_makers/issues/45#issue-1320772147) which mainstream slicers will load.

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

### Fingering Module
<p float="left">
  <img src="../../Documents/singleSolenoidWiringDiagram.PNG" height="300" />
</p>

1. Obtain and make all the parts listed above.
2. Insert a M3 nut into the internal side wall of the 3D-printed five solenoid container body, repeat this for each
location where a solenoid is required for tune hole fingering. 
3. Push the solenoid wires through the holes at the rear of the container body and insert a solenoid into each seating position (one for each tune hole across the recorder), making sure that the solenoid plunger can freely move up and down. 
4. Insert a M3 bolt through solenoid container and through the M3 nut to tighten the solenoids into position. Only a light finger tight is required. If the plunger does not move freely and gets stuck carefully un-tighten the bolt and move the solenoid until the plunger moves freely.
5. Repeat the above for each solenoid location in the five seater container body, the single container body and four seater container body
6. connected solenoid circuit following the wiring diagram 
    -   connect one solenoid contact to the common power rail.
    -   connect the other solenoid contacts to the middle pin (pin C) of the darlington transistor.
    -   connect the diode between the two solenoid contacts, make sure that the
white stripe on the diode is on the negative side of the connection. The
diode acts as a power snubber preventing power spikes from the solenoid
damaging the other electrical components.
    -   connect the resistor to pin B of the transistor then to one of the digital
ports of the arduino, the port depends on the tune hole the solenoid seals
down on, currently the thumb tune hole is to port 1 on the arduino.
    -   connect pin E of the transistor to the common ground rail.
7. Once the connections are made attach the finger pads to each of the the required solenoids. The square fingerpads with a concave seal should be used on the five seat container body solenoids. The small domed finger pads are intended for the two 3mm diameter holes in double tune holes. The large domed finger pads are intended for the 4mm diameter holes in the double tone holes. The extension arms can also be used for the larger 4mm diameter tone holes. 
8. Mark out on the plywood mounting frame the position of each tone hole and the top edge and bottom edge of the recorder. Aos mark out suitable locations for the solenoid cable holes to be drilled through the plywood mounting frame to connect later to the breadboard that will be placed at the back of the nmounting frame. When placing the solenoid container bodies into position onto the mounting frame, it is important to not mount them further than 10mm from the top and bottom edges of the recorder otherwise the solenoids will not seal against the holes when actuated. 
8. To attach the five solenoid container body to the recorder base frame insert a M3 nut in to the slot on the top and bottom of the container body, then align the container bodies as required to cover the holes and previously marked out. This may require some further measurements and tweaking on the plywood mounting frame.  
9. Mark out and attach the two recorder clamps as to ensure that the middle joint holes are directly under the five seater container body and that the single seater container body is located directly under the recorder thumb hole. Feel free to use a small piece of rubber to add grip to the recorder when in the clamp.
10. Secure all the components using 3mm nuts and bolts. 
11. Once completed seat your new recorder mounting frame with the new components added into the recorder base stand. It should now being standing vertically, making it easy for you to see the fingering actuation during play.
12. Test the placement of the components and adjust where required. To finish, thread the solenoid cables to the rear of the plywood moutning frame where they can then be connected onto the breadboard. 


### Acknowledgements
The page has been 'forked' from Andrew Henry's, <a href="https://gitlab.com/Andrew_Henry/automated-guitar">automated guitar player</a>


