/* from https://github.com/laurb9/StepperDriver/blob/master/examples/MultiAxis/MultiAxis.ino
 * and https://docs.arduino.cc/learn/communication/wire#controller-writer
 *
 * Improvements:
 * 1. Use array or something for multiple motors to avoid repeated functions
 * 2. Use interrupts for limit pins (Uno only has 2)
 * 3. Implement switching active if within threshold of end
 *      - if keeping track of each motor's position is difficult then maybe use getStepsRemaining before calling stop.
 *      - infact, stop returns the number of steps remaining! (as long)
 * 4. ENABLE/DISABLE steppers
*/



#include "Wire.h"
#include "BasicStepperDriver.h"
#include "MultiDriver.h"

// for both steppers
const int MOTOR_STEPS = 200;
const int MICROSTEPS = 1;

// stepper A
const int DIR_A = 6;
const int STEP_A = 7;

// stepper B
const int DIR_B = 8;
const int STEP_B = 9;

BasicStepperDriver stepperA(MOTOR_STEPS, DIR_A, STEP_A);
BasicStepperDriver stepperB(MOTOR_STEPS, DIR_B, STEP_B);

MultiDriver controller(stepperA, stepperB);

// limit pins
const int LIMIT_A_EMPTY = 2;
const int LIMIT_B_EMPTY = 3;
const int LIMIT_A_FULL = 4;
const int LIMIT_B_FULL = 5;

// a number definitely more than the number of steps from full to empty
const int DEFINITELY_ENOUGH_STEPS = 10000;

// number of steps from full to empty
int maxStepsA;
int maxStepsB;

char activeStepper = 'A';
bool stopped = true;

int reading = 0;

void setup() {

    Serial.begin(9600);
    Serial.println("Hello");

    // RPM set to 90 initially
    stepperA.begin(120, MICROSTEPS);
    stepperB.begin(120, MICROSTEPS);
    
    // set limit pins to read HIGH unless grounded by switch closed
    pinMode(LIMIT_A_EMPTY, INPUT_PULLUP);
    pinMode(LIMIT_B_EMPTY, INPUT_PULLUP);
    pinMode(LIMIT_A_FULL, INPUT_PULLUP);
    pinMode(LIMIT_B_FULL, INPUT_PULLUP);

    Serial.println("Pins setup. Just about to home.");
    
    /*
    getMaxStepsA();
    homeStepperA();
    getMaxStepsB();
    homeStepperB();
    */
    
    Wire.begin(4);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event
    //Serial.begin(9600);           // start serial for output

    
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    //Serial.println("In receiveEvent");

    if (2 <= Wire.available()) { // if two bytes were received

        reading = Wire.read();  // receive high byte (overwrites previous reading)
        reading = reading << 8;    // shift high byte to be high 8 bits
        reading |= Wire.read(); // receive low byte as lower 8 bits

        Serial.println(reading);   // print the reading
        // use highByte() and lowByte #defines to send the int as two bytes
/*
        // start or update blowing rpm
        if (reading > 0) {
            getActiveStepper().setRPM(reading);
           
            // if we had stopped then need to start again but if not updating RPM is enough
            if (stopped) {
                getActiveStepper().startMove(maxStepsA);
                stopped = false;
            }
        }
        // else reading == 0 and we want to stop blowing
        else {
            // stop the stepper currently blowing
            getActiveStepper().stop();
            stopped = true;
        }*/
    }
}

// https://stackoverflow.com/a/8914714
BasicStepperDriver& getActiveStepper() {
    switch (activeStepper)
    {
    case 'A':
        return stepperA;
        break;

    case 'B':
        return stepperB;
        break;
    
    default:
        break;
    }
}

void homeStepperA() {

    Serial.println("In Home A");

    // move towards home 
    stepperA.startMove(-DEFINITELY_ENOUGH_STEPS);
    
    //while stepper not at limit pin, move towards it.
    while (digitalRead(LIMIT_A_FULL) != LOW) {
       stepperA.nextAction();
    }
    stepperA.stop();
    Serial.println("Homed");
}

void getMaxStepsA() {

    Serial.println("In Max Steps A");
    
    // move to home position
    homeStepperA();

    // now at home set count to zero
    int steps = 0;

    // move to empty end, counting steps
    stepperA.startMove(DEFINITELY_ENOUGH_STEPS);
    while (digitalRead(LIMIT_A_EMPTY) != LOW) {
       stepperA.nextAction();
       steps++;
    }

    stepperA.stop();

    // set max steps
    maxStepsA = steps;
}

void homeStepperB() {
    // move towards home 
    stepperB.startMove(-DEFINITELY_ENOUGH_STEPS);
    
    //while stepper not at limit pin, move towards it.
    while (digitalRead(LIMIT_B_FULL) != LOW) {
       stepperB.nextAction();
    }
    stepperB.stop();
}

void getMaxStepsB() {
    
    // move to home position
    homeStepperB();
    
    // now at home set count to zero
    int steps = 0;

    // move to empty end, counting steps
    stepperB.startMove(DEFINITELY_ENOUGH_STEPS);
    while (digitalRead(LIMIT_B_EMPTY) != LOW) {
       stepperB.nextAction();
       steps++;
    }

    stepperB.stop();

    // set max steps
    maxStepsB = steps;
}

void loop() {

    // check limit pins
    if (digitalRead(LIMIT_A_EMPTY) == LOW) { // or reached its max steps?? use stepper.STOPPED? nope because 
        Serial.println("A Empty");
        /* 
         * set other one as active
         * check other one is at home? using its steps remaining while
         * update this one's steps remaining
         * set the other's rpm to this one
         * start a move to send this one home and the other blowing
        */ 
    }
    if (digitalRead(LIMIT_B_EMPTY) == LOW) {
        Serial.println("B Empty");

    }
    if (digitalRead(LIMIT_A_FULL) == LOW) {
        Serial.println("A Full");
        // set steps reamining as max and flag as ready
    }
    if (digitalRead(LIMIT_B_FULL) == LOW) {
        Serial.println("B Full");
        // set steps reamining as max and flag as ready
    }

    // do the next step
    controller.nextAction();
}