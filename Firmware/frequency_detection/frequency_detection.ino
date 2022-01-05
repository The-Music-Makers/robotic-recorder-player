/* -------------------------------------
 *  Arduino Frequency Detection Using FFT
 * -------------------------------------
 * This sketch builds upon code provided 
 * one the website:http://shorturl.at/zRU57.
 * It makes use of the arduinoFFT lib which 
 * can be installed via the libraries manager.
 * 
 * Written : Kyle Fogarty
 * Date : 27th Dec 2021
 */


#include "arduinoFFT.h"

#define SAMPLES 128             // Number of amplitude samples taken from microphone
#define SAMPLING_FREQUENCY 2000 // [Hz] -> Nyquist–Shannon sampling theorem 
                                //         requires sample freq = 2 * highest signal freq
                                //         that is to be recovered.
                                
#define MICROPHONE_PIN 0        // Microphone plugged into the Analog

arduinoFFT FFT = arduinoFFT();  // Instantiate the FFT module 
                                
                                // [μs] sampling period = 1 / (sampling freq)
unsigned int sampling_period_us round(1000000*(1.0/SAMPLING_FREQUENCY));
       
double FFTReal[SAMPLES];  // Array to hold the Real part of FT
double FFTIm[SAMPLES];    // Array to hold the Im part of FT
 
void setup() {Serial.begin(9600);}
 
void loop() {
  
/* ----------------
 * Signal Sampling
   ----------------*/
  
    for(int i=0; i<SAMPLES; i++)
    { unsigned long microseconds = micros();    
      FFTReal[i] = analogRead(MICROPHONE_PIN); // Obtain Sample
      FFTIm[i] = 0;
      while(micros() < (microseconds + sampling_period_us)){}
    }
 
/* ----------------
 *    Perform FFT
   ----------------*/

    // Compute the Fourier TF 
    FFT.Compute(FFTReal, FFTIm, SAMPLES, FFT_FORWARD); 
    FFT.ComplexToMagnitude(FFTReal, FFTIm, SAMPLES);
    double peak = FFT.MajorPeak(FFTReal, SAMPLES, SAMPLING_FREQUENCY);
 
/* ----------------
 * Print Freq at Peak
 *   and bin range
   ----------------*/
    Serial.print("Freq Detected: "); 
    Serial.print(peak);// Print out what frequency is the most dominant.
   
    double bin = peak / (SAMPLING_FREQUENCY/SAMPLES);
    int bin_low = bin; // int typecast will always floor the double
    int bin_high = bin_low + 1;
    Serial.print(" | Bin Range: ");
    Serial.print(bin_low*(SAMPLING_FREQUENCY/SAMPLES));
    Serial.print(" - ");
    Serial.println(bin_high*(SAMPLING_FREQUENCY/SAMPLES));
    delay(250);
}
