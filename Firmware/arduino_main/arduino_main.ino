/*
 *  Main Arduino sketch for Music Makers recorder.
 *
 *  Receives MIDI messages from a companion computer over the serial port.
 *  Actuates solenoids to cover holes on recorder replication the action of fingers.
 *  Actuates a single stepper motor, attached to a lead screw, to compress/expand an
 *  artificial lung to blow air through the recorder.
 * 
 *  Authors
 *  Date
 * 
 *  Licence
 */

// comment out to not compile debugging sections of code
#define DEBUG

// https://github.com/laurb9/StepperDriver
#include "BasicStepperDriver.h"

/////////////////////////
//    DECLARATIONS &   //
//      CONSTANTS      //
/////////////////////////

// define Note as a new type
typedef struct{
    bool fPattern[10]; // array of bools for finger pattern (10 holes to cover) 1 means hole covered
    int targetFreq; 
    int blowVel;
} Note;

//add program start time
unsigned long startMillis;
unsigned long currentMillis;

//add count to show how many notes have been played
unsigned int count = 0;

// define notes recorder can play
const int lowNote = 72; //C5
const int highNote = 86; //D6
const int arrSize = highNote - lowNote + 1; //create array using this to check for consistency
// define offset such that MIDInote - offset = index for note array
// lowest note on our recorder C5 (84) so offset is 85.
const int noteOffset = lowNote; //Review this line as change to noteOffset no longer required
// create a list of Note structures
// C5 is MIDI note 84 so we will access the desired note using that offset
// note range C5 to D6 is 15 notes

Note notes[arrSize] = {
  {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 523, 200}, //C5 (MIDI 72) https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
  {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, 554, 210}, //Db5 (MIDI 73)
  {{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 }, 587, 220}, //D5 (MIDI 74)
  {{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 }, 622, 230}, //Eb5 (MIDI 75)
  {{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }, 659, 240}, //E5 (MIDI 76)
  {{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 }, 698, 250}, //F5 (MIDI 77)
  {{ 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 }, 740, 260}, //Gb5 (MIDI 78)
  {{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, 784, 270}, //G5 (MIDI 79)
  {{ 1, 1, 1, 0, 1, 1, 1, 0, 0, 0 }, 831, 280}, //Ab5 (MIDI 80)
  {{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, 880, 290}, //A5 (MIDI 81)
  {{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 }, 932, 300}, //Bb5 (MIDI 82)
  {{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, 988, 310}, //B5 (MIDI 83)
  {{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, 1047, 320}, //C6 (MIDI 84)
  {{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, 1109, 330}, //Db6 (MIDI 85)
  {{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, 1175, 340}, //D6 (MIDI 86)
};


// define pins the solenoids are connected to in hole order starting with thumb
// usage: solenoidPins[2] returns pin corresponding to actuator covering hole 2
// Pin 7 & 8 are for the first double hole and 9 & 10 for the second
// Pin 11 is thumbhole
const int solenoidPins[10] = {11,2,3,4,5,6,7,8,9,10}; 

// stepper setup
#define MOTOR_STEPS 200
#define MICROSTEPS 1
#define DIR_PIN 12
#define STEP_PIN 13
#define INIT_RPM 100

// create stepper object
BasicStepperDriver stepper(MOTOR_STEPS, DIR_PIN,STEP_PIN);

//const int limitPin = 33;
const int maxSteps = 2000; // worked out experimentally
const int homeRPM = 300;
int stepsToEnd = maxSteps; // steps remaining to max position
const int endThreshold = 200; // after a note off, if motor is within this distance of end, it will home before another note is played

// MIDI channels 1-16 are zero based so minus 1 for byte
const byte channel = 0;

// construct status bytes where left hex digit represents the command and right the channel
const byte noteOn = 0x90 + channel;
const byte noteOff = 0x80 + channel;


/////////////////////////
//    FUNCTION DEFS    //
/////////////////////////

void setFingers(bool pattern[]){
    
    for (int f=0;f<10;f++){
        // set pin high/low according to pattern
        digitalWrite(solenoidPins[f], pattern[f]);
        
        #ifdef DEBUG
          //Serial.print("Pin ");
          //Serial.print(solenoidPins[f]);
          //Serial.print(": ");
          //Serial.println(pattern[f]);
        #endif
    }
}

bool isInRange(byte note) {
    if (note >= lowNote && note <= highNote) {
        return true;
    }
    else {
        return false;
    }
}

void doNoteOn(byte note, byte vel) {

    // convert from MIDI note number to index in our note array
    int ndx = note-noteOffset;
    #ifdef DEBUG
    //Serial.println("Doing Note On");
    //Serial.print("Index:");
    //Serial.println(note-noteOffset);
    #endif

    // set fingers
    setFingers(notes[ndx].fPattern);

    // start blowing
    // set RPM corresponding to note
    stepper.setRPM(notes[ndx].blowVel);

    //supporting print statments for debugging stepper
    //Serial.print("Stepper.getRPM():");
    //Serial.println(stepper.getRPM());

    //Serial.print("STEPS TO END: ");
    //Serial.println(stepsToEnd);
    
    // set motor to move all steps it has remaining (as we don't know how many steps we'll need)
    stepper.startMove(stepsToEnd);
}

void doNoteOff(byte vel) {
    
    // stop blowing
    stepper.stop();
    
    // all fingers off - unneccesary to function but will de-energise solenoids to let them rest
    // Update so that there is a check and only de-energise those that aren't needed on the following note
    bool fingersOff[10] = {0,0,0,0,0,0,0,0,0,0};
    setFingers(fingersOff);

    // if we are close to end, home the stepper before we play another note
    if (stepsToEnd < endThreshold) {
        Serial.println("END THRESHHOLD REACHED");
        homeStepper();
    }
}

void homeStepper() {

    //Serial.print("HOME STEPPER ROUTINE");
  
    // save current rpm so it can be reassigned after homing
    int rpm = stepper.getCurrentRPM();
    
    stepper.setRPM(homeRPM);
    stepper.move(-(maxSteps-stepsToEnd)); //double to make sure it definitely reaches home
    
    // while stepper not at limit pin, move towards it.
    //while (digitalRead(limitPin) != LOW) {
    //    stepper.nextAction();
    //}
    
    //home reached
    stepper.stop();
    stepsToEnd = maxSteps;
    stepper.setRPM(rpm); // set RPM to what it was before homing

    #ifdef DEBUG
    //Serial.println("Stepper reached home");
    #endif

    return;
}

/////////////////////////
//        SETUP        //
/////////////////////////

void setup() {

    startMillis = millis(); //initial program start time
    
    Serial.begin(115200); //9600
    
    // set all solenoid pins for OUTPUT
    for (int f=0;f<10;f++){
        pinMode(solenoidPins[f], OUTPUT);
        digitalWrite(solenoidPins[f], HIGH);
        delay(100);
        digitalWrite(solenoidPins[f], LOW);
    }

    stepper.begin(INIT_RPM, MICROSTEPS);

    // set limit pin to read HIGH unless grounded by switch closed
    //pinMode(limitPin, INPUT_PULLUP);

    homeStepper();

    // TESTING
    /*delay(2000);
    Serial.println("Set fingers note C5");
    Serial.print("Freq: ");
    Serial.println(notes[3].targetFreq);
    setFingers(notes[3].fPattern);
    */
}

/////////////////////////
//      MAIN LOOP      //
/////////////////////////

void loop(){



    // JB these don't need to be static
    byte cmdByte;
    byte noteByte;
    byte velByte;

    static byte currNote;

    // if stepper at end then home and let move continue
    if (stepsToEnd <= 0) {
        Serial.println("RUN OUT OF STEPS");
        homeStepper();
        stepper.startMove(stepsToEnd); // so move can be continued
    }

    // move another step at the right time
    // once nextAction called, program will sit in that function until the right time to pulse the motor.
    // its okay to call even if we don't want the motor to move because it will return if there are no steps to move.
    // EDIT: whilst the above is okay, don't want to decrement stepsToEnd so if we're checking stepper is stopped we might as well put nextAction in the loop too
    // stepper.getStepsRemaining() <= 0 probably quicker than stepper.getCurrentState() != stepper.STOPPED but should measure.
    if (stepper.getStepsRemaining() > 0) {
        stepper.nextAction();
        stepsToEnd--;  
    }

    // if data availabe, read serial port in expectation of a MIDI message
    if (Serial.available() > 0) {
        cmdByte = Serial.read();
        
        #ifdef DEBUG
        //Serial.print("Cmd: ");
        //Serial.println(cmdByte);
        #endif

        currentMillis = millis(); //gets current time 

        // if >= 128 it is a status byte so decode, else it's a surplus data byte so ignore
        if (cmdByte >= 128) {

            #ifdef DEBUG
            //Serial.println("CmdByte is a status byte. Inside if.");
            #endif

            //Serial.println("NOTE STARTS HERE");
            
            switch (cmdByte) {
                case noteOn:

                    // Counts courrent number of Note Ons
                    count++;

                    #ifdef DEBUG
                    Serial.println("NoteOn case");
                    Serial.print("Time in ms: ");
                    Serial.println( currentMillis);
                    Serial.print("Notes played: ");
                    Serial.println(count);
                    #endif

                    // read following data bytes
                    noteByte = Serial.read();
                    velByte = Serial.read();

                    #ifdef DEBUG
                    //Serial.print("Note: ");
                    //Serial.println(noteByte);
                    //Serial.print("Vel: ");
                    //Serial.println(velByte);       
                    #endif

                    // If note is valid then do NoteOn function 
                    if (isInRange(noteByte)) {
                        doNoteOn(noteByte, velByte);
                        currNote = noteByte;
                    }
                    else {
                      Serial.print("NOTE OUT OF RANGE");
                    }
                 
                    
                    break;

                case noteOff:

                    #ifdef DEBUG
                    Serial.println("NoteOff case");
                    Serial.print("Time in ms: ");
                    Serial.println( currentMillis);
                    #endif

                    // read following data bytes
                    noteByte = Serial.read();
                    velByte = Serial.read();

                    #ifdef DEBUG
                    //Serial.print("Note: ");
                    //Serial.println(noteByte);
                    //Serial.print("Vel: ");
                    //Serial.println(velByte);       
                    #endif

                    /* recorder only one note at time so any new note on cmd will overwrite a previous
                     * therefore must check the desired note to turn off is the one being played
                     * if not, the note is already off so ignore the command.
                     */
                    if (noteByte == currNote) {
                        doNoteOff(velByte);
                    }
                    
                    break;

                default:
                    // don't know how to handle the command so ignore
                    #ifdef DEBUG
                    Serial.println("Don't understand command. Ignoring.");
                    #endif
                    break;
            }
        }
    }
}
