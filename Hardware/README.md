# Hardware
You can either build the system as is or you may need to modify the design to fit your recorder. Please see [Modifying the Design](#modifying-the-design) for instructions.

## You Will Need

- 1 x Recorder - we used the Aulos A205.
- 1 x [Blowing Module](Blowing%20Module).
- 1 x [Fingering Module](Fingering%20Module).
- 1 x Arduino Mega (with USB cable).
- 1 x High sensitivity sound sensor module ([e.g.](https://www.amazon.co.uk/gp/product/B06WLHK6BY)).

## Assembly Instructions
1. Gather and make everything required in the 'You Will Need' list according to the instructions within each module.
2. Insert the recorder into the Fingering Module.
3. Push the mouthpiece connector of the Blowing Module onto the recorder mouthpiece.
4. Make connections to the Arduino Mega:
   - Connect 5V and GND to each of the Fingering Module, Blowing Module and Sound Sensor.
   - Connect the output of the sound sensor to pin A0.
   - Connect the STEP and DIR pins of the Blowing Module to pins 30 and 32 respectively.
   - Connect the control wire corresponding to each of the solenoids from the Fingering Module to pins D2 through D11.

## Modifying the Design
If you need to modify the design (for example the tone hole spacings on your recorder are different) the source of our CAD models is given using STEP files which can be found in each module's folder. These can be downloaded and edited using your favourite CAD platform. [FreeCAD](https://www.freecadweb.org/index.php) is a good open source option.