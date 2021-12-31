"""To be used with recv_MIDI_test.ino"""

import serial
import mido

ser = serial.Serial('COM3')

mid = mido.MidiFile('Raspberry_Pi\midi_examples\jingle_bells.mid')

for msg in mid.play():
    ser.write(msg.bin())