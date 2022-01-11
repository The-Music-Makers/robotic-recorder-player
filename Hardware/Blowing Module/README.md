# Blowing Module

## Bill of Materials

### Purchase
| Item | Quantity | Details |
| -------- | -------- | -------- |
| Stepper Motor | 1 | NEMA 17, 4 wire |
| Lead screw | 1 | 8 mm lead |
| Lead screw nut | 1 |  |
| Lead screw to motor coupler | 1 |  |
| Bottom bearing | 1 | To accept lead screw |
| M3 x 20 mm bolt and nut | 4 |  |
| DRV8825 motor driver | 1 |  |
| 100 uF capacitor | 1 |  |
| 12V 2A power supply | 1 |  |
| Lung walls: flexible concertina material | 300 mm | e.g [Ducting Hose](https://www.screwfix.com/p/manrose-pvc-flexible-ducting-hose-white-1m-x-100mm/17297)|
| Cable ties | 2 | 450 mm long |
| 8 mm tubing | 200 mm |  |
| Breadboard and jumper wires | 1 |  |

### Make
| Item | Quantity | Method | Details |
| - | - | - | - |
| Lung Base | 1 | 3D Print | [STL](lung-base.stl) |
| Lung Top | 1 | 3D Print | [STL](lung-top.stl) |
| Mouthpiece Connector | 1 | 3D Print | [STL](pipe-to-mouthpiece.stl) |

All of our parts were printed in PLA. 0.4 mm nozzle, 0.2 mm layer height, 2 walls, 20% infill are adequate settings. Depending on our printer you may need support for the Lung Base.

## Assembly Instructions

1. Obtain and make all the parts listed above.
2. Insert the bearing into the lung base and the lead screw nut into the lung top and attach using the M3 bolts and nuts.
3. Attach the lung walls to the base using a cable tie.
4. Thread the lead screw through the nut and into the bearing. Tighten the grub screws of the bearing onto the lead screw.
5. Attach the lung walls to the top using a cable tie.
6. Push the 8 mm tubing onto the lung base and the mouthpiece connector onto the tubing.
6. Use the coupler to attach the motor shaft to the lead screw, tightening the grub screws.
7. On a breadboard, using jumper wires, connect the stepper motor, motor driver, power supply and capacitor as detailed on the [DRV8825 page](https://www.pololu.com/product/2133).
8. Connect one end of each jumper wire 5V, GND, STEP, DIR pins ready for connection to the Arudino.