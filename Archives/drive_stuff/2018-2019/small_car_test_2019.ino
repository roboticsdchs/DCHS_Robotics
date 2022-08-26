#include <Servo.h>

Servo myservo;
int PWMA = 3;
int DIRA = 12;


void Forward(){
  digitalWrite(PWMA, HIGH);
  digitalWrite(DIRA, HIGH);
  delay(5000);
  digitalWrite(PWMA, LOW);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
}

void Backward(){
  digitalWrite(PWMA, HIGH);
  digitalWrite(DIRA, LOW);
  delay(5000);
  digitalWrite(PWMA, LOW);
}
void Left(){
  digitalWrite(PWMA, HIGH);
   myservo.write(90); 
  digitalWrite(DIRA, HIGH);
  delay(5000);
  myservo.write(60); 
  digitalWrite(PWMA, LOW);
}

void Right(){
   digitalWrite(PWMA, HIGH);
   myservo.write(30); 
  digitalWrite(DIRA, HIGH);
  delay(5000);
  myservo.write(60); 
 digitalWrite(PWMA, LOW);
}

void setup(){
  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  myservo.attach(6);
  Right();
}

void loop(){
}
 
//90 degrees = around 2500 ms
