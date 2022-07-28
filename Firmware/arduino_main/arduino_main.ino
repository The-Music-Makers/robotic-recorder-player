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
#include <Wire.h>
// Includes Wire Master Writer by Nicholas Zambetti <http://www.zambetti.com>

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
  {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 523, 130}, //C5 (MIDI 72) https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies
  {{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, 554, 140}, //Db5 (MIDI 73)
  {{ 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 }, 587, 150}, //D5 (MIDI 74)
  {{ 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 }, 622, 160}, //Eb5 (MIDI 75)
  {{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 }, 659, 170}, //E5 (MIDI 76)
  {{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 }, 698, 180}, //F5 (MIDI 77)
  {{ 1, 1, 1, 1, 0, 1, 1, 1, 0, 0 }, 740, 190}, //Gb5 (MIDI 78)
  {{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, 784, 200}, //G5 (MIDI 79)
  {{ 1, 1, 1, 0, 1, 1, 1, 0, 0, 0 }, 831, 220}, //Ab5 (MIDI 80)
  {{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, 880, 240}, //A5 (MIDI 81)
  {{ 1, 1, 0, 1, 1, 0, 0, 0, 0, 0 }, 932, 265}, //Bb5 (MIDI 82)
  {{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 }, 988, 290}, //B5 (MIDI 83)
  {{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, 1047, 320}, //C6 (MIDI 84)
  {{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, 1109, 330}, //Db6 (MIDI 85)
  {{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, 1175, 340}, //D6 (MIDI 86)
};



// define pins the solenoids are connected to in hole order starting with thumb
// usage: solenoidPins[2] returns pin corresponding to actuator covering hole 2
// Pin 7 & 8 are for the first double hole and 9 & 10 for the second
// Pin 11 is thumbhole
const int solenoidPins[10] = {45,47,49,51,53,37,35,39,41,43}; 

// MIDI channels 1-16 are zero based so minus 1 for byte
const byte channel = 0;

// construct status bytes where left hex digit represents the command and right the channel
const byte noteOn = 0x90 + channel;
const byte noteOff = 0x80 + channel;

// variable to start timing after a note off so fingers will de-energise after specified period
unsigned long idleTimeStart;
const int idleWait = 1000; //ms


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

void setRPM(int rpm){
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(highByte(rpm));              // sends one byte  
    Wire.write(lowByte(rpm));
    Wire.endTransmission();    // stop transmitting
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

    // set RPM corresponding to note
    setRPM(notes[ndx].blowVel);
}

void doNoteOff(byte vel) {
    
    // stop blowing
    setRPM(0);
    
    // UPDATE: undesirable so implementing a delay for before de-energising
    // all fingers off - unneccesary to function but will de-energise solenoids to let them rest
    // Update so that there is a check and only de-energise those that aren't needed on the following note
    //bool fingersOff[10] = {0,0,0,0,0,0,0,0,0,0};
    //setFingers(fingersOff);

    // record start time of timer
    idleTimeStart = millis();
}

/////////////////////////
//        SETUP        //
/////////////////////////

void setup() {

    Serial.begin(115200); //9600
    
    // set all solenoid pins for OUTPUT
    for (int f=0;f<10;f++){
        pinMode(solenoidPins[f], OUTPUT);
        digitalWrite(solenoidPins[f], HIGH);
        delay(100);
        digitalWrite(solenoidPins[f], LOW);
    }

    Wire.begin(); // join i2c bus (address optional for master)

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

    if ((millis() - idleTimeStart) > idleWait) {
        // if wait time has elapsed then de-energise fingers
        bool fingersOff[10] = {0,0,0,0,0,0,0,0,0,0};
        setFingers(fingersOff);
        // should disable stepper motor here too
    }
    
    // if data availabe, read serial port in expectation of a MIDI message
    if (Serial.available() > 0) {
        cmdByte = Serial.read();
        
        #ifdef DEBUG
        //Serial.print("Cmd: ");
        //Serial.println(cmdByte);
        #endif

        // if >= 128 it is a status byte so decode, else it's a surplus data byte so ignore
        if (cmdByte >= 128) {

            #ifdef DEBUG
            //Serial.println("CmdByte is a status byte. Inside if.");
            #endif

            //Serial.println("NOTE STARTS HERE");
            
            switch (cmdByte) {
                case noteOn:

                    #ifdef DEBUG
                    Serial.println("NoteOn case");
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
