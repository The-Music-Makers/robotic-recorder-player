# Inststructions for running the automated recorder
Note, these are intended for team members - not general makers.

## Edit and upload arduino sketch
- Open `src\arduino_main\arduino_main.ino`.
- Set `solenoidPins`.
- Set `channel` - likely to be 0.
- Ensure the notes you desire to play are defined in `notes` and `lowNote` and `highNote` are defined accordingly.
- Upload the sketch to the arduino.

## Send some MIDI messages
- Suggested to use the `jukebox_testing.py` utility as described in [this README](/Raspberry_Pi/README.md#using-the-jukebox_testingpy-utility)
- Note this can be run from the RaspberryPi or any companion computer.
