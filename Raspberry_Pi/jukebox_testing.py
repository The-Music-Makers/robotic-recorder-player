"""A utility that can be imported into an interactive Python session to aid in sending MIDI data to the Arduino.
To use, set Raspberry_Pi as working directory and run: from jukebox_testing import *. """

import serial
import mido
from time import sleep

def playFile(filename):
    """Plays specified file in midi_examples/ with reporting"""

    # load midi file
    mid = mido.MidiFile('midi_examples/' + filename)

    # play whilst reading messages arduino sends back
    for msg in mid.play():
        # midi msg converted to a byte array and sent via serial port
        ser.write(msg.bin())

        while ser.in_waiting > 0:
            print('Arduino says: ' + ser.readline().decode())

    print("Finished playing " + filename)

def sendMsg(msg):
    """Sends MIDI message with reporting. Construct MIDI message using mido.Message() and pass as argument to function."""
    # midi msg converted to a byte array and sent via serial port

    ser.write(msg.bin())

    sleep(0.2) # wait for arduino to do stuff

    while ser.in_waiting > 0:
        print('Arduino says: ' + ser.readline().decode())

def showHelp():
    print('''
        -------------------------------------------------------------------------------
                                        HELP
                                        ‾‾‾‾
            To send a single message use sendMsg(msg) where msg is a mido message 
            object e.g msg = mido.Message('note_on', note=60, velocity=64).
            sendMsg(msg) will print anything the arduino sends to the command line.

            To play a MIDI file use playFile(filename). The working directory must 
            be the music_makers repo root and the MIDI file must be saved in 
            midi_examples. Specify filename as a string and the function will print
            anything the arduino sends to the command line.

            To reshow this message call showHelp().
        -------------------------------------------------------------------------------
        ''')

print('''

====================================================
==           Welcome to jukebox_testing           ==
==     a utility to aid sending MIDI messages     ==
====================================================

''')

try:
    ser = serial.Serial('/dev/cu.usbmodem14201', 9600, timeout=0.1) #Note: the string should be COM3 or whatever port you connect your Arduino 
except serial.SerialException:
    print("Error opening serial port.")
else:
    if ser.is_open:
        print('Port open on ' + ser.port + '.')
    
    showHelp()

if __name__ == "__main__":
    # don't do anything - file is intended to be imported.
    print("Please import module to an interactive session.")