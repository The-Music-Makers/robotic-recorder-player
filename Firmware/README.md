# Music Makers

The main script that needs to be uploaded to the Arduino board is located within the `arduino_main` folder of this directory. To upload the sketch we recommend that you use the Arduino IDE, which can be obtained from [arduino.cc](https://www.arduino.cc/en/software).

## Getting started

### `arduino_main.ino`
1. Open the Arduino IDE and load in the `arduino_main.ino` file (`File -> Open -> select_file`).
1. Ensure `solenoidPins` are set to what they were plugged in to during the hardware build.
1. Set `channel` (default `0`).
1. Ensure the notes you desire to play are defined in `notes` and `lowNote` and `highNote` are defined accordingly.
1. Upload the sketch (see [below](#upload))

### `arduino_lung.ino`
1. Open the Arduino IDE and load in the `arduino_main.ino` file (`File -> Open -> select_file`).
1. Ensure DIR, STEP and all four limit pin connections are set to what they were plugged in to during the hardware build for both stepper motor drivers.
1. Upload the sketch (see [below](#upload))

## Upload

The firmware can be uploaded through `Sketch -> Upload` or by pressing the upload button.
<img align="center" width="200" src="../Documents/upload.png" />

Connect the Arduino board to the computer and set the port it is attached to:
  
- `Tools -> Board -> Arduino AVR Boards -> *Select the Arduino Board*`
- `Tools -> Processor -> *Select the Arduino Prosessor*`
- `Tools -> Port -> *Select the USB port*`
