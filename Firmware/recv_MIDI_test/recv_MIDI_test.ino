byte cmdByte;
byte noteByte;
byte velByte;

void setup() {
    Serial.begin(9600);
    
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
}

void loop() {
    if (Serial.available() >= 3){
        cmdByte = Serial.read();
        noteByte = Serial.read();
        velByte = Serial.read();

        // light for 1 sec when msg received 
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);

        if (cmdByte == 0x90) {
            // note on channel 1 (or 0)
            // flash LED if this msg received
            for (int i=0;i<30;i++){
                digitalWrite(LED_BUILTIN, HIGH);
                delay(50);
                digitalWrite(LED_BUILTIN, LOW);
                delay(50);
            }
        }
    }
}