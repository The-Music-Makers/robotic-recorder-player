//#include "AltoSaxVib_C4.h"
//#include "Piano_C4_Clean.h"
//#include "Guitar_C5.h"
//#include "C4.h"

#define MICROPHONE_PIN 0 

// Sample Frequency in Hz
const int SAMPLING_FREQUENCY = 8000;
unsigned int sampling_period_us = 1000000*(1.0/SAMPLING_FREQUENCY);

const int SAMPLES = 256;

int rawData[SAMPLES];

/*
int i,k;
long sum, sum_old;
int thresh = 0;
float freq_per = 0;
byte pd_state = 0;
*/

void setup() {
  Serial.begin(115200);
  }

void loop() {

    // record data 
    for(int i=0; i<SAMPLES; i++)
        { unsigned long microseconds = micros();    
        rawData[i] = analogRead(MICROPHONE_PIN); // Obtain Sample
        while(micros() < (microseconds + sampling_period_us)){}
    }
    /*
    for(int i=0; i<SAMPLES; i++) {
      Serial.println(rawData[i]);  
    }*/
    
    
    for(int k=0; k<SAMPLES-128; k++) {

        long sum =0;

        // do autocorrelation
        for(int m=0; m<128; m++) {
            sum += (rawData[m]*rawData[m+k])/1000;
        }

        Serial.println(sum);
        
    }

    delay(1000);
    
  /*
  sum = 0;
  pd_state = 0;
  int period = 0;
  for(i=0; i < len; i++)
  {
    // Autocorrelation
    sum_old = sum;
    sum = 0;
    for(k=0; k < len-i; k++) sum += (rawData[k]-128)*(rawData[k+i]-128)/256;


    // Peak Detect State Machine
    if (pd_state == 2 && (sum-sum_old) <=0) 
    {
      period = i;
      pd_state = 3;
    }
    if (pd_state == 1 && (sum > thresh) && (sum-sum_old) > 0) pd_state = 2;
    if (!i) {
      thresh = sum * 0.5;
      pd_state = 1;
    }
  }
  // Frequency identified in kHz
  freq_per = sample_freq/period;
  Serial.println(freq_per);*/
}
