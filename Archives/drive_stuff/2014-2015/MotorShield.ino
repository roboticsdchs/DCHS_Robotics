byte inA = 4;
byte pwmA = 5;
byte pwmB = 6;
byte inB = 7;

void setup() {
  pinMode(inA, OUTPUT);
  pinMode(inB, OUTPUT);
}

void loop() {
  /*
  digitalWrite(inA, HIGH);
  int value;
  for(value = 0; value <= 255; value += 5){
    analogWrite(pwmA, value);
    delay(50);
  }
  */
  
  analogWrite(pwmB, 100);
  digitalWrite(inB, LOW);
  delay(100);
  analogWrite(pwmB, 0);
  delay(1000);
  analogWrite(pwmB, 100);
  digitalWrite(inB, HIGH);
  delay(100);
  analogWrite(pwmB, 0);
  
  delay(1000);
}
