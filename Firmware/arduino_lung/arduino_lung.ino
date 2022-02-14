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
const int HOME_RPM = 200;

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
// temporary fix to add to max steps and make sure it reaches switch
const int SOME_EXTRA = 400;

// number of steps from full to empty
int maxStepsA;
int maxStepsB;
// number of steps left to empty - only updated on stop()
int stepsRemA;
int stepsRemB;

bool aIsFilling = false;
bool bIsFilling = false;

char activeStepper = 'A';
bool stopped = true;

int reading = 0;

void setup() {

    Serial.begin(115200);
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
    
    Serial.println("Getting Max Steps A.");
    getMaxStepsA();
    Serial.println("Homing A.");
    homeStepperA();
    Serial.println("Getting Max Steps B.");
    getMaxStepsB();
    Serial.println("Homing B.");
    homeStepperB();

    Serial.print("Max Steps A: ");
    Serial.println(maxStepsA);
    Serial.print("Max Steps B: ");
    Serial.println(maxStepsB);

    activeStepper = 'A';
    stepsRemA = maxStepsA + SOME_EXTRA;
    stepsRemB = maxStepsB + SOME_EXTRA;
    
    
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

        Serial.print("RPM Request: ");
        Serial.println(reading);   // print the reading
        // use highByte() and lowByte #defines to send the int as two bytes

        // start or update blowing rpm
        if (reading > 0) {
            Serial.print("Setting RPM. Current A RPM: ");
            Serial.print(stepperA.getRPM());

            //getActiveStepper().setRPM(reading); NOT WORKING

            switch (activeStepper)
                {
                case 'A':
                    stepperA.setRPM(reading);
                    break;

                case 'B':
                    stepperB.setRPM(reading);
                    break;
                
                default:
                    break;
                }

            Serial.print("New A RPM: ");
            Serial.println(stepperA.getRPM());
            

                      
            // if we had stopped then need to start again but if not updating RPM is enough
            if (stopped) {
                switch (activeStepper)
                {
                case 'A':
                    stepperA.startMove(stepsRemA);
                    Serial.println("A started.");
                    break;

                case 'B':
                    stepperB.startMove(stepsRemB);
                    break;
                
                default:
                    break;
                }
                stopped = false;
            }
        }
        // else reading == 0 and we want to stop blowing
        else {
            // stop the stepper currently blowing
            switch (activeStepper)
            {
            case 'A':
                stepsRemA = stepperA.stop();
                break;

            case 'B':
                stepsRemB = stepperB.stop();
                break;
            
            default:
                break;
            }
            stopped = true;
        }
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
    Serial.println("Homed");
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
    if (digitalRead(LIMIT_A_EMPTY) == LOW && activeStepper == 'A') { // or reached its max steps?? at start of loop see if active stepper has stopped whist stopped flag not set.
        Serial.println("A Empty");
        
        stepsRemA = 0;
        int currentRPM = stepperA.getCurrentRPM();
        stepperA.setRPM(HOME_RPM);
        aIsFilling = true;
        
        if (bIsFilling) {
            // in case it hasn't filled by now
            int remaining = stepperB.stop();
            // set the steps B will have til empty
            stepsRemB = DEFINITELY_ENOUGH_STEPS - remaining;
            bIsFilling = false;
        } 
        activeStepper = 'B';
        stepperB.setRPM(currentRPM);

        Serial.print("Starting move. Steps for B: ");
        Serial.println(stepsRemB);

        controller.startMove(-DEFINITELY_ENOUGH_STEPS, stepsRemB);

    }
    if (digitalRead(LIMIT_B_EMPTY) == LOW && activeStepper == 'B') {
        Serial.println("B Empty");

        stepsRemB = 0;
        int currentRPM = stepperB.getCurrentRPM();
        stepperB.setRPM(HOME_RPM);
        bIsFilling = true;
        
        if (aIsFilling) {
            // in case it hasn't filled by now
            int remaining = stepperA.stop();
            // set the steps B will have til empty
            stepsRemA = DEFINITELY_ENOUGH_STEPS - remaining;
            aIsFilling = false;
        } 
        activeStepper = 'A';
        stepperA.setRPM(currentRPM);

        Serial.print("Starting move. Steps for A: ");
        Serial.println(stepsRemA);

        controller.startMove(stepsRemA, -DEFINITELY_ENOUGH_STEPS);

    }
    if (digitalRead(LIMIT_A_FULL) == LOW && aIsFilling) {
        Serial.println("A Full");
        
        //
        stepperA.stop();
        aIsFilling = false;
        stepsRemA = maxStepsA;
    }
    if (digitalRead(LIMIT_B_FULL) == LOW && bIsFilling) {
        Serial.println("B Full");

        //
        stepperB.stop();
        bIsFilling = false;
        stepsRemB = maxStepsB;
        
    }

    // do the next step
    controller.nextAction();
}