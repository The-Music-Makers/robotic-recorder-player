# Music Makers

The main script that needs to be uploaded to the Arduino board is located within the `arduino_main` folder of this directory. To upload the sketch we recommend that you use the Arduino IDE, which can be obtained from [arduino.cc](https://www.arduino.cc/en/software).

## Getting started

1. Open the Arduino IDE and load in the `arduino_main.ino` file (`File -> Open -> select_file`).
1. Ensure `solenoidPins` and the motor `DIR` and `STEP` pins are set to what they were plugged in to during the hardware build.
1. Set `channel` (default `0`).
1. Ensure the notes you desire to play are defined in `notes` and `lowNote` and `highNote` are defined accordingly.
1. Connect the Arduino board to the computer and set the port it is attached to (`Tools -> Ports -> your_port`)
1. Upload the sketch to the board using upload button (2nd button on the top left of the IDE)