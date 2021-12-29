// comment out to not compile debugging sections of code
#define DEBUG

// define Note as a new type
typedef struct{
    bool fPattern[10]; // array of bools for finger pattern (10 holes to cover) 1 means hole covered
    int targetFreq; 
    int blowVel;
} Note;

// define notes recorder can play
const int lowNote = 84; //C5
const int highNote = 87; //Eb5
const int arrSize = highNote - lowNote + 1; //create array using this to check for consistency
// define offset such that MIDInote - offset = index for note array
// lowest note on our recorder C5 (84) so offset is 85.
const int noteOffset = lowNote + 1;
// create a list of Note structures
// C5 is MIDI note 84 so we will access the desired note using that offset
// note range C5 to D6 is 15 notes
Note notes[arrSize] = {
  {{1,1,1,1,1,1,1,1,1,1}, 523, 0}, //C5
  {{1,1,1,1,1,1,1,1,1,0}, 554, 0}, //Db5
  {{1,1,1,1,1,1,1,1,0,0}, 587, 0}, //D5
  {{1,1,1,1,1,1,1,0,0,0}, 622, 0}, //Eb5
};

// define pins the solenoids are connected to in hole order starting with thumb
// usage: solenoidPins[2] returns pin corresponding to actuator covering hole 2
const int solenoidPins[10] = {9,2,3,4,5,6,7,8,10,11};

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
          Serial.print("Pin ");
          Serial.print(solenoidPins[f]);
          Serial.print(": ");
          Serial.println(pattern[f]);
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

    #ifdef DEBUG
    Serial.println("Doing Note On");
    Serial.print("Index:");
    Serial.println(note-noteOffset);
    #endif

    // set fingers
    setFingers(notes[note-noteOffset].fPattern);

    // start blowing
}

void doNoteOff(byte vel) {
    
    // stop blowing
    
    // all fingers off - unneccesary to function but will de-energise solenoids to let them rest
    bool fingersOff[10] = {0,0,0,0,0,0,0,0,0,0};
    setFingers(fingersOff);
}

/////////////////////////
//        SETUP        //
/////////////////////////

void setup() {
    
    Serial.begin(9600);
    
    // set all solenoid pins for OUTPUT
    for (int f=0;f<10;f++){
        pinMode(solenoidPins[f], OUTPUT);
        digitalWrite(solenoidPins[f], HIGH);
        delay(100);
        digitalWrite(solenoidPins[f], LOW);
    }

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

    if (Serial.available() > 0) {
        cmdByte = Serial.read();
        
        #ifdef DEBUG
        Serial.print("Cmd: ");
        Serial.println(cmdByte);
        #endif

        Serial.println("Test");


        // if >= 128 it is a status byte so decode, else it's a surplus data byte so ignore
        if (cmdByte >= 128) {

            #ifdef DEBUG
            Serial.println("CmdByte is a status byte. Inside if.");
            #endif
            
            switch (cmdByte) {
                case noteOn:

                    #ifdef DEBUG
                    Serial.println("NoteOn case");
                    #endif

                    // read following data bytes
                    noteByte = Serial.read();
                    velByte = Serial.read();

                    #ifdef DEBUG
                    Serial.print("Note: ");
                    Serial.println(noteByte);
                    Serial.print("Vel: ");
                    Serial.println(velByte);       
                    #endif

                    if (isInRange(noteByte)) {
                        doNoteOn(noteByte, velByte);
                        currNote = noteByte;
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
                    Serial.print("Note: ");
                    Serial.println(noteByte);
                    Serial.print("Vel: ");
                    Serial.println(velByte);       
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
                    Serial.print("Don't understand command. Ignoring.");
                    #endif
                    break;
            }
        }
    }
}
