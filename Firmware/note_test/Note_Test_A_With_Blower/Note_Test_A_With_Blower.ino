// Music Makers

// Blower Note Test Program - Note A - 
// Activate pins 11, 2 & 3 only (thumb and first two middle body holes) and blower using pins 12 & 13

// Garry Clawson
// 2nd Jan 2022
// Used this guide to setup the motor: https://www.makerguides.com/a4988-stepper-motor-driver-arduino-tutorial/ 

//Example sketch to control a stepper motor with A4988 stepper motor driver and Arduino without a library. 
//More info: https://www.makerguides.com

// Define stepper motor connections and steps per revolution:
#define dirPin 4
#define stepPin 5
#define stepsPerRevolution 200

int solenoidPin11 = 11; 
int solenoidPin2 = 2; 
int solenoidPin3 = 3; 

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(solenoidPin11, OUTPUT);
  pinMode(solenoidPin2, OUTPUT); 
  pinMode(solenoidPin3, OUTPUT);     
   
}

void loop() {

  delay(1000);

  // Set the fingers into position for note A
  digitalWrite(solenoidPin11, HIGH);
  digitalWrite(solenoidPin2, HIGH);
  digitalWrite(solenoidPin3, HIGH);
  
  // Set the spinning direction clockwise: i.e. DOWN
  digitalWrite(dirPin, HIGH);
  
  // Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 22 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(700); //Sets speed of motor between 300 - 500 is best. Lower = faster
    digitalWrite(stepPin, LOW);
    delayMicroseconds(700);
  } 

  // Set the fingers into off position
  digitalWrite(solenoidPin11, LOW);
  digitalWrite(solenoidPin2, LOW);
  digitalWrite(solenoidPin3, LOW);
   
  delay(1000);
  
  // Set the spinning direction counterclockwise: i.e. UP
  digitalWrite(dirPin, LOW);
  //Spin the stepper motor 5 revolutions fast:
  for (int i = 0; i < 22 * stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }

}
