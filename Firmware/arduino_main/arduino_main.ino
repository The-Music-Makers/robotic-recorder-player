/*
 *  Music Makers: Robotic Recorder Player
 *  Main Arduino sketch
 *
 *  Copyright © 2022 Music Makers
 *
 *  This file is part of the Music Makers' Robotic Recorder Player project.
 *  The Robotic Recorder Player is an open source hardware and software
 *  project. A copy of the licences that cover this project are found in the
 *  root of this repository.
 *
 *  Description
 *  • Receives MIDI messages from a companion computer over the serial port.
 *  • Actuates solenoids to cover tone holes on the recorder, replicating the
 *    action of fingers.
 *  • Sends a blowing RPM via I2C to the lung module to produce air.
 */

// comment out to not compile debugging sections of code
#define DEBUG

#include "BasicStepperDriver.h" // https://github.com/laurb9/StepperDriver
#include <Wire.h>

/////////////////////////
//    DECLARATIONS &   //
//      CONSTANTS      //
/////////////////////////

// define range of notes recorder can play
const int lowNote = 72;  // C5
const int highNote = 86; // D6
const int arrSize = highNote - lowNote + 1;
// define offset such that MIDInote - offset = index for note array
// assigning to new name for readability
const int noteOffset = lowNote;

// define Note as a new type
typedef struct
{
    bool fPattern[10];
    int targetFreq;
    int blowVel;
} Note;

/* fPattern: Array of bools for finger pattern - 1 means hole covered.
 * targetFreq: Pitch of note. Determined from https://www.inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies.
 * blowVel: RPM to produce correct pitch note. Currently determined
 *          experimentally. In future to be determined by program.
 */
// create array of Note structures
Note notes[arrSize] = {
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 523, 130},  // C5 (MIDI 72)
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 554, 140},  // Db5 (MIDI 73)
    {{1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 587, 150},  // D5 (MIDI 74)
    {{1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, 622, 160},  // Eb5 (MIDI 75)
    {{1, 1, 1, 1, 1, 1, 0, 0, 0, 0}, 659, 170},  // E5 (MIDI 76)
    {{1, 1, 1, 1, 1, 0, 1, 1, 1, 1}, 698, 180},  // F5 (MIDI 77)
    {{1, 1, 1, 1, 0, 1, 1, 1, 0, 0}, 740, 190},  // Gb5 (MIDI 78)
    {{1, 1, 1, 1, 0, 0, 0, 0, 0, 0}, 784, 200},  // G5 (MIDI 79)
    {{1, 1, 1, 0, 1, 1, 1, 0, 0, 0}, 831, 220},  // Ab5 (MIDI 80)
    {{1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, 880, 240},  // A5 (MIDI 81)
    {{1, 1, 0, 1, 1, 0, 0, 0, 0, 0}, 932, 265},  // Bb5 (MIDI 82)
    {{1, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 988, 290},  // B5 (MIDI 83)
    {{1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 1047, 320}, // C6 (MIDI 84)
    {{0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, 1109, 330}, // Db6 (MIDI 85)
    {{0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, 1175, 340}, // D6 (MIDI 86)
};

// pattern for all fingers released
bool fingersOff[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// define pins the solenoids are connected to in hole order starting with thumb
const int solenoidPins[10] = {45, 47, 49, 51, 53, 37, 35, 39, 41, 43};

// define MIDI channel
// MIDI channels 1-16 are zero based so minus 1 for byte value
const byte channel = 0;

// construct status bytes
// left hex digit represents the command and right digit the channel
const byte noteOn = 0x90 + channel;
const byte noteOff = 0x80 + channel;

/* Don't want to remove fingers immediately after note off command, especially 
 * in the case of repeated notes so leave them energised. However, don't want 
 * them energised forever as that would lead to overheating. A timer is started
 * after a note off command and fingers released if idleWait time reached. 
 */ 
unsigned long idleTimeStart;
const int idleWait = 2000; // ms


/////////////////////////
//    FUNCTION DEFS    //
/////////////////////////

void setFingers(bool pattern[])
{
    for (int f = 0; f < 10; f++)
    {
        // set pin high/low according to pattern
        digitalWrite(solenoidPins[f], pattern[f]);
    }
}

bool isInRange(byte note)
{
    if (note >= lowNote && note <= highNote)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void setRPM(int rpm)
{
    // send rpm to lung module via I2C
    // from Wire Master Writer by Nicholas Zambetti <http://www.zambetti.com>
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(highByte(rpm)); // sends one byte
    Wire.write(lowByte(rpm));
    Wire.endTransmission(); // stop transmitting
}

void doNoteOn(byte note, byte vel)
{
    // convert from MIDI note number to index in our note array
    int ndx = note - noteOffset;

    #ifdef DEBUG
    Serial.print("Doing NoteOn | ");
    Serial.print("MIDI: ");
    Serial.print(note);
    Serial.print(" | Index: ");
    Serial.println(ndx);
    #endif

    // set fingers
    setFingers(notes[ndx].fPattern);

    // set RPM corresponding to note
    setRPM(notes[ndx].blowVel);
}

void doNoteOff(byte vel)
{
    // stop blowing
    setRPM(0);

    #ifdef DEBUG
    Serial.println("Doing NoteOff");
    #endif

    // record start time of timer
    idleTimeStart = millis();
}


/////////////////////////
//        SETUP        //
/////////////////////////

void setup()
{
    // serial used to receive MIDI and report debugging
    Serial.begin(115200);

    // set all solenoid pins for OUTPUT
    for (int f = 0; f < 10; f++)
    {
        pinMode(solenoidPins[f], OUTPUT);
        digitalWrite(solenoidPins[f], HIGH);
        delay(100);
        digitalWrite(solenoidPins[f], LOW);
    }

    // join i2c bus
    Wire.begin();
}


/////////////////////////
//      MAIN LOOP      //
/////////////////////////

void loop()
{
    // MIDI messages decoded into these variables
    byte cmdByte;
    byte noteByte;
    byte velByte;

    // store current note being played between loop iterations
    static byte currNote;

    // check if idleWait time has elapsed to de-energise fingers
    if ((millis() - idleTimeStart) > idleWait)
    {
        setFingers(fingersOff);
    }

    // if data availabe, read serial port in expectation of a MIDI message
    if (Serial.available() > 0)
    {
        cmdByte = Serial.read();

        #ifdef DEBUG
        Serial.print("Cmd byte: ");
        Serial.println(cmdByte);
        #endif

        // if >= 128 it is a status byte so decode, 
        // else it's a surplus data byte so ignore
        if (cmdByte >= 128)
        {
            switch (cmdByte)
            {
            case noteOn:

                // read following data bytes
                noteByte = Serial.read();
                velByte = Serial.read();

                #ifdef DEBUG
                Serial.print("Note byte: ");
                Serial.print(noteByte);
                Serial.print(" | Vel byte: ");
                Serial.println(velByte);
                #endif

                // if note is valid then do NoteOn function
                if (isInRange(noteByte))
                {
                    doNoteOn(noteByte, velByte);
                    currNote = noteByte;
                }
                else
                {
                    #ifdef DEBUG
                    Serial.print("Note out of range");
                    #endif
                }

                break;

            case noteOff:

                // read following data bytes
                noteByte = Serial.read();
                velByte = Serial.read();
                
                #ifdef DEBUG
                Serial.print("Note byte: ");
                Serial.print(noteByte);
                Serial.print(" | Vel byte: ");
                Serial.println(velByte);
                #endif

                /* Recorder only plays one note at time so a new noteOn cmd will
                 * overwrite a previous. Therefore must check the noteOff
                 * command corresponds to the note currently being played.
                 * If not, the note is already off so ignore the command.
                 */
                if (noteByte == currNote)
                {
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