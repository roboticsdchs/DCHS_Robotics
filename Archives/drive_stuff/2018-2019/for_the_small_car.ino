int servo = 6;
int dirA = 12;
int pwmA = 3;

void Forward(){
  digitalWrite(pwmA, HIGH);
  digitalWrite(dirA, HIGH);
  delay(5000);
  digitalWrite(pwmA, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
}

void Backward(){
  digitalWrite(pwmA, HIGH);
  digitalWrite(dirA, LOW);
  delay(5000);
  digitalWrite(pwmA, LOW);
}
void Left(){
  digitalWrite(pwmA, HIGH);
  digitalWrite(dirA, HIGH);
  analogWrite(servo, 105);
  delay(5000);
  analogWrite(servo, 90);
  digitalWrite(pwmA, LOW);
}

void Right(){
   digitalWrite(pwmA, HIGH);
  digitalWrite(dirA, HIGH);
  analogWrite(servo, 45);
  delay(5000);
  analogWrite(servo, 90);
  digitalWrite(pwmA, LOW);
}

void setup(){
  pinMode(dirA, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(servo, OUTPUT);
  Forward();
}
