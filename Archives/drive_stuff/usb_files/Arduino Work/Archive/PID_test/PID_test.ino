int pwma = 8; //sets the power pin for motor A (8 is OUT4)
int pwmb = 9; //sets the power pin for motor B

void setup() {
  pinMode(pwma, OUTPUT); //sets the pwma pin to output
  pinMode(pwmb, OUTPUT); //sets the pwmb pin to output
}

void loop() {
  analogWrite(pwma, 200); //turns the motor on, using analog
  delay(100); //delays for 1s
  analogWrite(pwma, 200); //turns the motor off, using analog
  delay(100);
}
