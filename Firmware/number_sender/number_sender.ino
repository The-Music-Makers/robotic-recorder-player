// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI Peripheral device
// Refer to the "Wire Peripheral Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

int x = 150;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);

  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(highByte(x));              // sends one byte  
  Wire.write(lowByte(x));
  Wire.endTransmission();    // stop transmitting

  Serial.println(x);
}



void loop()
{
  /*
  Wire.beginTransmission(4); // transmit to device #4
  //Wire.write("x is ");        // sends five bytes
  Wire.write(highByte(x));              // sends one byte  
  Wire.write(lowByte(x));
  Wire.endTransmission();    // stop transmitting

  Serial.println(x);

  x=x+20;
  delay(1000);
  */
}
