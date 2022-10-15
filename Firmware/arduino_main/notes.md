# Notes for Arduino sketch

- Note velocity not currently handled. The plan is to map blowing velocity of MIDI message to a motor acceleration (in steps/s^2 ?). The motor speed will ramp up and down to the set RPM.
- For initial testing purposes, only notes C5 to D6 implemented. Any notes sent outside this range will be ignored.
- Testing showed we wanted to keep fingers energised after a note on but if that was infinite then overheating occured. Currently a 2 second delay is hard coded which is undesirable. If heating issues fixed then could keep energised and decode an end of song MIDI message.
- Target frequency currently not utilised but plans exist to do so.