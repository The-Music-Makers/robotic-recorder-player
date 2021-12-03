#define DEBUG

typedef struct{
    bool fPattern[10]; // array of bools for finger pattern (10 holes to cover)
    int targetFreq; 
    int blowVel;
} Note;

//Note noteC5 = {{1,1,1,1,1,1,1,1,1,1}, 523, 0};

// note range C5 to D6 is 15 notes
Note notes[4] = {
  {{1,1,1,1,1,1,1,1,1,1}, 523, 0}, //C5
  {{1,1,1,1,1,1,1,1,1,0}, 554, 0}, //Db5
  {{1,1,1,1,1,1,1,1,0,0}, 587, 0}, //D5
  {{1,1,1,1,1,1,1,0,0,0}, 622, 0}, //Eb5
};

// usage: solenoidPins[2] returns pin corresponding to actuator covering hole 2
int solenoidPins[10] = {2,3,4,5,6,7,8,9,10,11};

/////////////////////////
//    FUNCTION DEFS    //
/////////////////////////

void setFingers(bool pattern[]){
    for (int f=0;f<10;f++){
        digitalWrite(solenoidPins[f], pattern[f]);
        #ifdef DEBUG
          Serial.print(solenoidPins[f]);
          Serial.print(": ");
          Serial.println(pattern[f]);
        #endif
    }
}


void setup() {
    Serial.begin(9600);
    
    for (int f=0;f<10;f++){
        pinMode(solenoidPins[f], OUTPUT);
    }

    delay(2000);

    Serial.println("Set fingers note C5");
    Serial.print("Freq: ");
    Serial.println(notes[3].targetFreq);
    setFingers(notes[3].fPattern);
}

void loop(){}
