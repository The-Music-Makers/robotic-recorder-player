//Music Makers
//21 Nov 2021
//Code to demonstrate each solenoid actuating in sequence and parrallel

int solenoidPin1 = 1;
int solenoidPin2 = 2;
int solenoidPin3 = 3;
int solenoidPin4 = 4;
int solenoidPin5 = 5;
int solenoidPin6 = 6;
int solenoidPin7 = 7;

void setup() {
  // Setup each of the solenoid pins on the board

  pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);
  pinMode(solenoidPin3, OUTPUT);
  pinMode(solenoidPin4, OUTPUT);
  pinMode(solenoidPin5, OUTPUT);
  pinMode(solenoidPin6, OUTPUT);
  pinMode(solenoidPin7, OUTPUT);

}

void loop() {
//Sequenxes though 6 pins and holds 3 at high state and then returns them to a low state

  digitalWrite(solenoidPin1, HIGH);
  delay(300);
  digitalWrite(solenoidPin2, HIGH);
  delay(300);
  digitalWrite(solenoidPin3, HIGH);
  delay(300);


  digitalWrite(solenoidPin3, LOW);
  delay(300);
  digitalWrite(solenoidPin2, LOW);
  delay(300);
  digitalWrite(solenoidPin1, LOW);


  digitalWrite(solenoidPin4, HIGH);
  delay(300);
  digitalWrite(solenoidPin5, HIGH);
  delay(300);
  digitalWrite(solenoidPin6, HIGH);
  delay(300);


  digitalWrite(solenoidPin6, LOW);
  delay(300);
  digitalWrite(solenoidPin5, LOW);
  delay(300);
  digitalWrite(solenoidPin4, LOW);
  delay(300);


//SHOWS 3 PINS ACTUATED AT ONCE THEN DEACTIVATED

  digitalWrite(solenoidPin1, HIGH);
  digitalWrite(solenoidPin3, HIGH);
  digitalWrite(solenoidPin6, HIGH);

  delay(300);

  digitalWrite(solenoidPin1, LOW);
  digitalWrite(solenoidPin3, LOW);
  digitalWrite(solenoidPin6, LOW);
  
}
