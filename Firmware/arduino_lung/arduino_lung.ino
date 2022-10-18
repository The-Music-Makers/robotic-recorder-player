/*
 *  Music Makers: Robotic Recorder Player
 *  Lung Arduino sketch
 *
 *  Copyright © 2022 Music Makers
 *
 *  This file is part of the Music Makers' Robotic Recorder Player project.
 *  The Robotic Recorder Player is an open source hardware and software
 *  project. A copy of the licences that cover this project are found in the
 *  root of this repository.
 *
 *  Description
 *  • Receives desired blowing velocity as integers via I2C.
 *  • Actuates stepper motors via drivers to turn at desired RPM
 *  • Implements a twin lung system such that one can fill while other empties.
 */

/*
 * Resources
 * https://github.com/laurb9/StepperDriver/blob/master/examples/MultiAxis/MultiAxis.ino
 * https://docs.arduino.cc/learn/communication/wire#controller-writer
 */

/*
 * Improvements:
 * 1. Use array or something for multiple motors to avoid repeated functions
 *    → or have reference variable that points to the active lung
 * 2. Use interrupts for limit pins (Uno only has 2)
 * 3. Implement switching active if within threshold of end
 * 4. ENABLE/DISABLE steppers
 */

// comment out to not compile debugging sections of code
#define DEBUG

#include "Wire.h"
#include "BasicStepperDriver.h"
#include "MultiDriver.h"


/////////////////////////
//    DECLARATIONS &   //
//      CONSTANTS      //
/////////////////////////

// for both steppers
const int MOTOR_STEPS = 200;
const int MICROSTEPS = 1;
const int HOME_RPM = 300;

// stepper A
const int DIR_A = 6;
const int STEP_A = 7;

// stepper B
const int DIR_B = 8;
const int STEP_B = 9;

// create stepper objects
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


/////////////////////////
//    FUNCTION DEFS    //
/////////////////////////

void homeStepperA()
{

    // move towards home
    stepperA.startMove(-DEFINITELY_ENOUGH_STEPS);

    // while stepper not at limit pin, move towards it.
    while (digitalRead(LIMIT_A_FULL) != LOW)
    {
        stepperA.nextAction();
    }
    stepperA.stop();

#ifdef DEBUG
    Serial.println("Stepper A reached home");
#endif
}

void getMaxStepsA()
{

    // move to home position
    homeStepperA();

    // now at home set count to zero
    int steps = 0;

    // move to empty end, counting steps
    stepperA.startMove(DEFINITELY_ENOUGH_STEPS);
    while (digitalRead(LIMIT_A_EMPTY) != LOW)
    {
        stepperA.nextAction();
        steps++;
    }

    stepperA.stop();

    // set max steps
    maxStepsA = steps;

#ifdef DEBUG
    Serial.println("Stepper A ready");
#endif
}

void homeStepperB()
{
    // move towards home
    stepperB.startMove(-DEFINITELY_ENOUGH_STEPS);

    // while stepper not at limit pin, move towards it.
    while (digitalRead(LIMIT_B_FULL) != LOW)
    {
        stepperB.nextAction();
    }
    stepperB.stop();

#ifdef DEBUG
    Serial.println("Stepper B reached home");
#endif
}

void getMaxStepsB()
{

    // move to home position
    homeStepperB();

    // now at home set count to zero
    int steps = 0;

    // move to empty end, counting steps
    stepperB.startMove(DEFINITELY_ENOUGH_STEPS);
    while (digitalRead(LIMIT_B_EMPTY) != LOW)
    {
        stepperB.nextAction();
        steps++;
    }

    stepperB.stop();

    // set max steps
    maxStepsB = steps;

#ifdef DEBUG
    Serial.println("Stepper A ready");
#endif
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
    if (2 <= Wire.available()) // if two bytes were received
    { 
        reading = Wire.read();  // receive high byte
        reading = reading << 8; // shift high byte to be high 8 bits
        reading |= Wire.read(); // receive low byte as lower 8 bits

        #ifdef DEBUG
        Serial.print("RPM Request: ");
        Serial.println(reading); // print the reading
        #endif

        // start or update blowing rpm
        if (reading > 0)
        {
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

            // if we had stopped then need to start again 
            // but if not updating RPM (done above) is enough
            if (stopped)
            {
                switch (activeStepper)
                {
                case 'A':
                    stepperA.startMove(stepsRemA);
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
        else
        {
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

// // https://stackoverflow.com/a/8914714
// BasicStepperDriver& getActiveStepper() {
//     switch (activeStepper)
//     {
//     case 'A':
//         return stepperA;
//         break;

//     case 'B':
//         return stepperB;
//         break;

//     default:
//         break;
//     }
// }


/////////////////////////
//        SETUP        //
/////////////////////////

void setup()
{
    #ifdef DEBUG
    Serial.begin(115200);
    #endif

    // setup steppers
    stepperA.begin(HOME_RPM, MICROSTEPS);
    stepperB.begin(HOME_RPM, MICROSTEPS);

    // set limit pins to read HIGH unless grounded by switch closed
    pinMode(LIMIT_A_EMPTY, INPUT_PULLUP);
    pinMode(LIMIT_B_EMPTY, INPUT_PULLUP);
    pinMode(LIMIT_A_FULL, INPUT_PULLUP);
    pinMode(LIMIT_B_FULL, INPUT_PULLUP);

    // home steppers and get limits
    getMaxStepsA();
    homeStepperA();
    getMaxStepsB();
    homeStepperB();

    #ifdef DEBUG
    Serial.print("Max Steps A: ");
    Serial.println(maxStepsA);
    Serial.print("Max Steps B: ");
    Serial.println(maxStepsB);
    #endif

    activeStepper = 'A';
    stepsRemA = maxStepsA + SOME_EXTRA;
    stepsRemB = maxStepsB + SOME_EXTRA;

    // join i2c bus with address #4
    Wire.begin(4);
    // register event              
    Wire.onReceive(receiveEvent);
}


/////////////////////////
//      MAIN LOOP      //
/////////////////////////

void loop()
{
    // check limit pins
    if (digitalRead(LIMIT_A_EMPTY) == LOW && activeStepper == 'A')
    {
        // if A reaches empty whilst active
        // stop it and get RPM to transfer to B and start
        stepsRemA = 0;
        int currentRPM = stepperA.getCurrentRPM();
        stepperA.setRPM(HOME_RPM);
        aIsFilling = true;

        if (bIsFilling)
        {
            // in case it hasn't filled by now
            int remaining = stepperB.stop();
            // set the steps B will have til empty
            stepsRemB = DEFINITELY_ENOUGH_STEPS - remaining;
            bIsFilling = false;
        }
        activeStepper = 'B';
        stepperB.setRPM(currentRPM);

        #ifdef DEBUG
        Serial.println("A Empty. Starting B.");
        #endif
        
        // start A moving to home B blowing
        controller.startMove(-DEFINITELY_ENOUGH_STEPS, stepsRemB);
    }
    if (digitalRead(LIMIT_B_EMPTY) == LOW && activeStepper == 'B')
    {
        // as per above but for B empty
        stepsRemB = 0;
        int currentRPM = stepperB.getCurrentRPM();
        stepperB.setRPM(HOME_RPM);
        bIsFilling = true;

        if (aIsFilling)
        {
            int remaining = stepperA.stop();
            stepsRemA = DEFINITELY_ENOUGH_STEPS - remaining;
            aIsFilling = false;
        }
        activeStepper = 'A';
        stepperA.setRPM(currentRPM);

        #ifdef DEBUG
        Serial.println("B Empty. Starting A.");
        #endif
        
        // start A blowing and Bmoving to home
        controller.startMove(stepsRemA, -DEFINITELY_ENOUGH_STEPS);
    }
    if (digitalRead(LIMIT_A_FULL) == LOW && aIsFilling)
    {
        #ifdef DEBUG
        Serial.println("A Full");
        #endif
        
        // A is full, stop it
        stepperA.stop();
        aIsFilling = false;
        stepsRemA = maxStepsA;
    }
    if (digitalRead(LIMIT_B_FULL) == LOW && bIsFilling)
    {
        #ifdef DEBUG
        Serial.println("A Full");
        #endif
        
        // B is full, stop it
        stepperB.stop();
        bIsFilling = false;
        stepsRemB = maxStepsB;
    }

    // do the next step
    controller.nextAction();
}
