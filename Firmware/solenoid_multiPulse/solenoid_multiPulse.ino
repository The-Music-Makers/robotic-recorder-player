int solenoidPin1 = 1;
int solenoidPin2 = 2;
int solenoidPin3 = 3;
int solenoidPin4 = 4;
int solenoidPin5 = 5;
int solenoidPin6 = 6;
int solenoidPin7 = 7;

void setup() {
  // put your setup code here, to run once:

  pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);
  pinMode(solenoidPin3, OUTPUT);
  pinMode(solenoidPin4, OUTPUT);
  pinMode(solenoidPin5, OUTPUT);
  pinMode(solenoidPin6, OUTPUT);
  pinMode(solenoidPin7, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(solenoidPin1, HIGH);
  delay(300);
  digitalWrite(solenoidPin1, LOW);
  delay(300);

  digitalWrite(solenoidPin2, HIGH);
  delay(300);
  digitalWrite(solenoidPin2, LOW);
  delay(300);

  digitalWrite(solenoidPin3, HIGH);
  delay(300);
  digitalWrite(solenoidPin3, LOW);
  delay(300);
  
  digitalWrite(solenoidPin4, HIGH);
  delay(300);
  digitalWrite(solenoidPin4, LOW);
  delay(300);

  digitalWrite(solenoidPin5, HIGH);
  delay(300);
  digitalWrite(solenoidPin5, LOW);
  delay(300);

  digitalWrite(solenoidPin6, HIGH);
  delay(300);
  digitalWrite(solenoidPin6, LOW);
  delay(300);

  digitalWrite(solenoidPin7, HIGH);
  delay(300);
  digitalWrite(solenoidPin7, LOW);
  delay(300);
  
}
