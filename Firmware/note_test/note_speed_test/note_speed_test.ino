// Music Makers

// Note Spped Test
// Activate pins 2 & 3 from fully open to closed as many times per second as possible and read repsonses

// Garry Clawson
// 9th Jan 2022


int solenoidPin7 = 7; 
int solenoidPin8 = 8; 

void setup() {
  // Declare pins as output:
  pinMode(solenoidPin7, OUTPUT); 
  pinMode(solenoidPin8, OUTPUT);     
   
}

void loop() {
  
  // the lower the delay the faster the repsonse
  delay(40);
  // Set the fingers into position for note A
  digitalWrite(solenoidPin7, HIGH);
  digitalWrite(solenoidPin7, HIGH);
  delay(40);
  digitalWrite(solenoidPin7, LOW);
  digitalWrite(solenoidPin8, LOW);


}
