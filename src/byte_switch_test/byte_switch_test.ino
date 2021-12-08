void setup() {
    Serial.begin(9600);
}

void loop() {
    byte a = B11110000;
    byte b = 0xf0;
    // not this: byte c = 11110000;
    Serial.print(a);
}