// https://blog.wildan.us/2017/11/03/arduino-fast-er-sampling-rate/
// add "defines": ["__AVR_ATmega328P__", ..... to fix intellisense

const byte adcPin = 0;  // A0
const int MAX_RESULTS = 256;
const int WINDOW_SIZE = 64;
volatile int results [MAX_RESULTS];
volatile int resultNumber;

long autoCorr[MAX_RESULTS-WINDOW_SIZE];

// ADC complete ISR
ISR (ADC_vect)
  {
  if (resultNumber >= MAX_RESULTS)
    ADCSRA = 0;  // turn off ADC
  else
    results [resultNumber++] = ADC;
  }  // end of ADC_vect
  
EMPTY_INTERRUPT (TIMER1_COMPB_vect);
 
void setup ()
  {
  Serial.begin(115200); // set baudrate
  Serial.println();

  // use 3.3V analog reference
  // analogReference(EXTERNAL); not working?
  
  // reset Timer 1
  TCCR1A  = 0;
  TCCR1B  = 0;
  TCNT1   = 0;
  TCCR1B  = bit (CS11) | bit (WGM12);  // CTC, prescaler of 8
  TIMSK1  = bit (OCIE1B); 
  OCR1A   = 39;    
  OCR1B   = 39; // 20 uS - sampling frequency 50 kHz

  ADCSRA  =  bit (ADEN) | bit (ADIE) | bit (ADIF); // turn ADC on, want interrupt on completion
  ADCSRA |= bit (ADPS2);  // Prescaler of 16
  ADMUX   = bit (REFS0) | (adcPin & 7);
  ADCSRB  = bit (ADTS0) | bit (ADTS2);  // Timer/Counter1 Compare Match B
  ADCSRA |= bit (ADATE);   // turn on automatic triggering
}

void loop () {
    while (resultNumber < MAX_RESULTS) { }

    // remove dc bias of 1.25V: 1.25/5 * 1023 = 256

    for (int tau=0; tau<MAX_RESULTS-WINDOW_SIZE; tau++){
        for (int j=0; j<WINDOW_SIZE; j++){
            autoCorr[tau] = results[j]-256 * results[j + tau]-256;
        }
    }
    
    //for (int i = 0; i < MAX_RESULTS; i++) {Serial.println (results [i]);}
    for (int i = 0; i < MAX_RESULTS-WINDOW_SIZE; i++) {Serial.println (autoCorr[i]);}

    delay(1000);

    resultNumber = 0; // reset counter
    ADCSRA =  bit (ADEN) | bit (ADIE) | bit (ADIF)| bit (ADPS2) | bit (ADATE); // turn ADC ON
}