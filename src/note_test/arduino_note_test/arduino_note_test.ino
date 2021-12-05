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

int solenoidPin1 = 1;
int solenoidPin2 = 2;
int solenoidPin3 = 3;
int solenoidPin4 = 4;
int solenoidPin5 = 5;
int solenoidPin6 = 6;
int solenoidPin7 = 7;


// create a function that makes the solenoids high or low for the corresponding note
// and returns the frequency of the desired note
int play_note(string note) {

  // array for each note to define the finger pattern
  // order is thumb, L1, L2, L3, R1, R2, mainR3, smallR3, mainR4, smallR4
  // where L = lefthand, R = righthand and 1=indexfinger
  int c5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  int d_flat5[]= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
  int d5[] = { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };
  int e_flat5[] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 };
  int e5[] = { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 };
  int f5[] = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
  int g_flat5[] = { 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 };
  int g5[] = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };
  int a_flat5[] = { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0 };
  int a5[] = { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
  int b_flat5[] = { 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 };
  int b5[] = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
  int c6[] = { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
  int d_flat6[] = { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
  int d6[] = { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };

  // get the write fingering for the note specified when the function is called
  if (note == "c5") {
    int note_array[] = c5;
  } else if (note == "d_flat5") {
    int note_array[] = d_flat5;
  } else if (note == "d5") {
    int note_array[] = d5;
  } else if (note == "e_flat5") {
    int note_array[] = e_flat5;
  } else if (note == "e5") {
    int note_array[] = e5;
  } else if (note == "f5") {
    int note_array[] = f5;
  } else if (note == "g_flat5") {
    int note_array[] = g_flat5;
  } else if (note == "g5") {
    int note_array[] = g5;
  } else if (note == "a_flat5") {
    int note_array[] = a_flat5;
  } else if (note == "a5") {
    int note_array[] = a5;
  } else if (note == "b_flat5") {
    int note_array[] = b_flat5;
  } else if (note == "b5") {
    int note_array[] = b5;
  } else if (note == "c6") {
    int note_array[] = c6;
  } else if (note == "d_flat6") {
    int note_array[] = d_flat6;
  } else if (note == "d6") {
    int note_array[] = d6;
  } else {
    int note_array[] = b5;
  }
    
  
  // actuate the solednoids according to the fingering
  if (note_array[1] == 1) {
    digitalWrite(solenoidPin7, HIGH)
  } else {
    digitalWrite(solenoidPin7, LOW)
  }

  if (note_array[2] == 1) {
    digitalWrite(solenoidPin6, HIGH)
  } else {
    digitalWrite(solenoidPin6, LOW)
  }

  if (note_array[3] == 1) {
    digitalWrite(solenoidPin5, HIGH)
  } else {
    digitalWrite(solenoidPin5, LOW)
  }

  if (note_array[4] == 1) {
    digitalWrite(solenoidPin4, HIGH)
  } else {
    digitalWrite(solenoidPin4, LOW)
  }

  if (note_array[5] == 1) {
    digitalWrite(solenoidPin3, HIGH)
  } else {
    digitalWrite(solenoidPin3, LOW)
  }

  if (note_array[6] == 1) {
    digitalWrite(solenoidPin2, HIGH)
  } else {
    digitalWrite(solenoidPin2, LOW)
  }

  if (note_array[7] == 1) {
    digitalWrite(solenoidPin1, HIGH)
  } else {
    digitalWrite(solenoidPin1, LOW)
  }

  return 0;

}


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

  play_note("b5");
  stepper.rotate(360);
  
  //delay(100);
  
  play_note("a5");
  stepper.rotate(360);
  
  //delay(100);
    
  play_note("g5");
  stepper.rotate(360);

  //delay(100);

  play_note("a5");
  stepper.rotate(360);
 
  delay(500);

  stepper.rotate(-360*5);

  /*
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
