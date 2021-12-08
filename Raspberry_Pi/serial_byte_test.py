"""A little script to try sending bytes to the arduino and a few manipulation tasks of bytes in Python"""

import serial
from time import sleep

ser = serial.Serial('COM3')
print('Open: ', ser.is_open)

# pyserial API docs: https://pyserial.readthedocs.io/en/latest/pyserial_api.html
# useful resource: https://www.devdungeon.com/content/working-binary-data-python

sleep(2) # to fix vs code doing funny things with arduino

abyte = b'\xf0'
print('A byte: ', abyte, ' Type: ', type(abyte))

# using byte_test.ino where arduino just reads a byte and sends it back using Serial.write() - not print
ser.write(abyte)
while ser.in_waiting == 0:
    print('In waiting: ', ser.in_waiting)
    sleep(0.2)
rb = ser.read()
print('Sent byte: ', abyte, ' Received byte: ', rb, ' Type: ', type(rb))


# using byte_math_test.ino where arduino reads a byte adds 1 sends it back, hopefully
ser.write(abyte)
while ser.in_waiting == 0:
    print('In waiting: ', ser.in_waiting)
    sleep(0.2)
rb = ser.read()
sent_byte_as_int = int.from_bytes(abyte,byteorder='big') 
recv_byte_as_int = int.from_bytes(rb,byteorder='big')
print('Sent byte: ', sent_byte_as_int, ' + 1 = ?', ' Received byte: ', recv_byte_as_int) # yay, it works


an_int = 16
now_a_byte = an_int.to_bytes(1,byteorder='big')
print('An int: ', an_int, ' Now a byte: ', now_a_byte, ' Type: ', type(now_a_byte))

bin_int = int('11000011',2)
print('Int from bin: ', bin_int, ' Type: ', type(bin_int))
another_byte = bin_int.to_bytes(1,byteorder='big')
print('Now a byte: ', another_byte, ' Type: ', type(another_byte))

# https://docs.python.org/3/library/stdtypes.html#int.to_bytes
# https://docs.python.org/3/library/stdtypes.html#bytes
# NB if wanting to use bytes() and not int.to_bytes() (I don't know which is better)
# DOES NOT WORK: bytes(240)
# DOES WORK      bytes([240])

ser.close()
print('Open: ', ser.is_open)