#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 250

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 30
#define STEP 32
//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

//int solenoidPin1 = 1;
int solenoidPin2 = 2;
int solenoidPin3 = 3;
int solenoidPin4 = 4;
int solenoidPin5 = 5;
int solenoidPin6 = 6;
int solenoidPin7 = 7;

void setup() {
  // put your setup code here, to run once:

  //pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);
  pinMode(solenoidPin3, OUTPUT);
  pinMode(solenoidPin4, OUTPUT);
  pinMode(solenoidPin5, OUTPUT);
  pinMode(solenoidPin6, OUTPUT);
  pinMode(solenoidPin7, OUTPUT);

  stepper.begin(RPM, MICROSTEPS);
  // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
  // stepper.setEnableActiveState(LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(solenoidPin7, HIGH);
  stepper.rotate(360);
  
  //delay(100);
  
  digitalWrite(solenoidPin6, HIGH);
  stepper.rotate(360);
  
  //delay(100);
    
  digitalWrite(solenoidPin5, HIGH);
  stepper.rotate(360);

  //delay(100);

  digitalWrite(solenoidPin5, LOW);
  stepper.rotate(360);

  digitalWrite(solenoidPin6, LOW);
  stepper.rotate(360);
  

  digitalWrite(solenoidPin7, LOW);
  
  delay(500);

  stepper.rotate(-360*5);

 
  
  /*
  digitalWrite(solenoidPin4, HIGH);
  delay(300);
  digitalWrite(solenoidPin4, LOW);
  delay(300);

  digitalWrite(solenoidPin5, HIGH);
  delay(300);
  digitalWrite(solenoidPin5, LOW);
  delay(300);

  digitalWrite(solenoidPin6, HIGH);
  delay(300);
  digitalWrite(solenoidPin6, LOW);
  delay(300);

  digitalWrite(solenoidPin7, HIGH);
  delay(300);
  digitalWrite(solenoidPin7, LOW);
  delay(300);
  */
  
}
