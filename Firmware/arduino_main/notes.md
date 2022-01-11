# Notes for Arduino sketch

## Blowing
- `maxSteps` and `homeRPM` to be worked out experimentally.
- `ENABLE` currently not utilised.
- No acceleration behaviour currently implemented. The plan is to map blowing velocity of MIDI message to a motor acceleration (in steps/s^2 ?). The motor speed will ramp up and down to the set RPM.
- Currently only implemented for one lung. Behaviour is somewhat unsophisticated. In `loop()` it checks stepper is not at maximum extent before moving another step. If it is, motor will home and then execution will continue, preserving the current move. When a note off is called, if the motor is within a threshold of the end, it will home before starting a new note.

## ♫ Notes ♫
For initial testing purposes, only notes C5 to D#5 implemented. Any notes sent outside this range will be ignored.