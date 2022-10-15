/*
 *  Music Makers: Robotic Recorder Player
 *  Number Sender test sketch
 *
 *  Copyright © 2022 Music Makers
 *
 *  This file is part of the Music Makers' Robotic Recorder Player project.
 *  The Robotic Recorder Player is an open source hardware and software
 *  project. A copy of the licences that cover this project are found in the
 *  root of this repository.
 *
 *  Description
 *  • Sends numbers over I2C to test the arduino_lung functionality
 */

#include <Wire.h>

void setup()
{
    // from Wire Master Writer by Nicholas Zambetti <http://www.zambetti.com>
    Wire.begin();
    Serial.begin(9600);

    int x = 150;

    Wire.beginTransmission(4);
    Wire.write(highByte(x));
    Wire.write(lowByte(x));
    Wire.endTransmission();

    Serial.println(x);
    delay(2000);

    x = 0;
    Wire.beginTransmission(4);
    Wire.write(highByte(x));
    Wire.write(lowByte(x));
    Wire.endTransmission();

    Serial.println(x);
    delay(2000);

    x = 180;
    Wire.beginTransmission(4);
    Wire.write(highByte(x));
    Wire.write(lowByte(x));
    Wire.endTransmission();

    Serial.println(x);
}

void loop() {}