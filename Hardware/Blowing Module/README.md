# Blowing Module

<p float="left">
  <img src="../../Documents/blowing_module_assembly_overview.png" width="1200" />
</p>
<p float="left">
  <img src="../../Documents/blowing_module_assembly_overview_2.png" width="1200" />
</p>

## Bill of Materials

### Purchase
| Item | Quantity | Details | Example Supplier |
| -------- | -------- | -------- | ------- |
| Board (plywood or breadboard) | 1 | 350 x 250 x 15 mm | |
| Stepper Motor | 2 | NEMA 17, 4 wire | [Ooznest](https://ooznest.co.uk/product/nema17-stepper-motors/?attribute_pa_model=1-8-1703hs168a-62oz-1-68a)|
| Lead screw | 2 | 8 mm lead, 290 mm | [Ooznest](https://ooznest.co.uk/product/acme-8mm-lead-screw/?attribute_pa_screw-length=290mm)|
| Lead screw nut | 2 | | [Ooznest](https://ooznest.co.uk/product/acme-nut/) |
| Lead screw to motor coupler | 2 | | [Ooznest](https://ooznest.co.uk/product/rigid-motor-shaft-coupler/?attribute_pa_size=5x8mm) |
| Bearing | 2 |  Flange[^bearing] bearing, 8 mm ID ||
| M3 x 20 mm bolt and nut | 8 | | [Kayfast](https://www.kayfast.co.uk/category/537/Metric-Socket-Cap-Screws) |
| M3 x 16 mm bolt | 8 | | [Kayfast](https://www.kayfast.co.uk/category/537/Metric-Socket-Cap-Screws) |
| M5 x 25 mm bolt and nut | 4 | | [Kayfast](https://www.kayfast.co.uk/category/537/Metric-Socket-Cap-Screws) |
| Pan head wood screw | 16 | 1/2" x no.6 (12 mm x 3.5 mm) | [Toolstation](https://www.toolstation.com/self-tapping-pan-head-pozi-screw/p74035) *or* [Kayfast](https://www.kayfast.co.uk/category/584/Pozi-Pan-Self-Tapping-Screws)|
| DRV8825 motor driver | 2 |  |
| 100 uF capacitor | 1 |  |
| 12V 2A power supply | 1 |  |
| Lung walls: flexible concertina material | 2 x 300 mm | e.g Ducting Hose | [Screwfix](https://www.screwfix.com/p/manrose-pvc-flexible-ducting-hose-white-1m-x-100mm/17297)|
| Cable ties | 4 | 450 mm long | |
| 8 mm tubing | 200 mm |  | |
| Stripboard, wires, connectors *OR* breadboard[^breadboard] and jumper wires |  |  |

[^breadboard] Whilst a breadboard can be used, we recommend soldering to a stripboard for reliability.
[^bearing] A pillowblock bearing could also be used if the bearing support was modified but we had flange bearings so used them.

### Make
| Item | Quantity | Method | Model |
| - | - | - | - |
| Bottom cap | 2 | 3D Print | [`bottom-cap.3mf`](bottom-cap.3mf) |
| Bottom cap support | 2 | 3D Print | [`bottom-cap-support.3mf`](bottom-cap-support.3mf) |
| Top cap | 2 | 3D Print | [`top-cap.3mf`](top-cap.3mf) |
| Limit switch mount | 2 | 3D Print | [`limit-switch-mount.3mf`](limit-switch-mount.3mf)
| Hose fitting | 2 | 3D Print | [`hose-fitting.3mf`](hose-fitting.3mf)
| Plug fitting | 2 | 3D Print | [`plug.3mf`](plug.3mf)|
| Mouthpiece connector | 1 | 3D Print | [`pipe-to-mouthpiece.3mf`](pipe-to-mouthpiece.3mf)|

All of our parts were printed in PLA. 0.4 mm nozzle, 0.2 mm layer height, 2 walls, 20% infill are adequate settings. Depending on our printer you may need support for the Lung Base.

### Combining air

## Assembly Instructions

<p float="left">
  <img src="../../Documents/blower_circuit_diagram.png" height="400" />
</p>

1. Obtain and make all the parts listed above.
2. Insert the bearing into the lung base and the lead screw nut into the lung top and attach using the M3 bolts and nuts.
3. Attach the lung walls to the base using a cable tie.
4. Thread the lead screw through the nut and into the bearing. Tighten the grub screws of the bearing onto the lead screw.
5. Attach the lung walls to the top using a cable tie.
6. Push the 8 mm tubing onto the lung base and the mouthpiece connector onto the tubing.
6. Use the coupler to attach the motor shaft to the lead screw, tightening the grub screws.
7. On a breadboard, using jumper wires, connect the stepper motor, motor driver, power supply and capacitor as detailed on the [DRV8825 page](https://www.pololu.com/product/2133).
8. Connect one end of each jumper wire 5V, GND, STEP, DIR pins ready for connection to the Arudino.
