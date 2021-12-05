#include <Arduino.h>
#include "BasicStepperDriver.h"
// bethan - unsure what needs to be included for the arduino to run c++, i think there is a library for it
#include <vector>
#include <map>

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
float play_note(string note) {

  //create a map that stores the frequency in Hz (floats) indexed by note name (strings)
  // note: in future could change the note name to the MIDI int 
  std::map<std::string, std::float> frequencies;

  frequencies["c5"] = 523.25;
  frequencies["d_flat5"] = 554.37;
  frequencies["d5"] = 587.33;
  frequencies["e_flat5"] = 622.25;
  frequencies["e5"] = 659.25;
  frequencies["f5"] = 698.46;
  frequencies["g_flat5"] = 739.99;
  frequencies["g5"] = 783.99;
  frequencies["a_flat5"] = 830.61;
  frequencies["a5"] = 880.00;
  frequencies["b_flat5"] = 932.33;
  frequencies["b5"] = 987.77;
  frequencies["c6"] = 1046.50;
  frequencies["d_flat6"] = 1108.73;
  frequencies["d6"] = 1174.66;

  //declare the map that uses the note's name as a key, and has a 
  //vector that stores the note's fingering
  std::map< std::string, std::vector<int> > fingering;

  // order is thumb, L1, L2, L3, R1, R2, mainR3, smallR3, mainR4, smallR4
  // where L = lefthand, R = righthand and 1=indexfinger
  fingering["c5"] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
  fingering["d_flat5"] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
  fingering["d5"] = { 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };
  fingering["e_flat5"] = { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 };
  fingering["e5"] = { 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 };
  fingering["f5"] = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
  fingering["g_flat5"] = { 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 };
  fingering["g5"] = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };
  fingering["a_flat5"] = { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0 };
  fingering["a5"] = { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
  fingering["b_flat5"] = { 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 };
  fingering["b5"] = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
  fingering["c6"] = { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
  fingering["d_flat6"] = { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
  fingering["d6"] = { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };

  std::vector<int> note_fingering = fingering[note];
  digitalWrite(solenoidPin7, HIGH)

  // based on the current fingering where L1=pin7 and R4=pin1 and there are missing solenoids
  // update once all solenoids have been added 
  if (fingering[note][1] == 1) {
    digitalWrite(solenoidPin7, HIGH)
  } else {
    digitalWrite(solenoidPin7, LOW)
  }

  if (fingering[note][2] == 1) {
    digitalWrite(solenoidPin6, HIGH)
  } else {
    digitalWrite(solenoidPin6, LOW)
  }

  if (fingering[note][3] == 1) {
    digitalWrite(solenoidPin5, HIGH)
  } else {
    digitalWrite(solenoidPin5, LOW)
  }

  if (fingering[note][4] == 1) {
    digitalWrite(solenoidPin4, HIGH)
  } else {
    digitalWrite(solenoidPin4, LOW)
  }

  if (fingering[note][5] == 1) {
    digitalWrite(solenoidPin3, HIGH)
  } else {
    digitalWrite(solenoidPin3, LOW)
  }

  if (fingering[note][6] == 1) {
    digitalWrite(solenoidPin2, HIGH)
  } else {
    digitalWrite(solenoidPin2, LOW)
  }

  if (fingering[note][7] == 1) {
    digitalWrite(solenoidPin1, HIGH)
  } else {
    digitalWrite(solenoidPin1, LOW)
  }
  
  float freq;
  freq=frequencies[note];
  return freq;
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
