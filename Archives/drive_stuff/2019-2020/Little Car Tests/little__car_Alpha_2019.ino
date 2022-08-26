#include <Servo.h>


Servo myservo;
int PWMA = 3;
int DIRA = 12;

void Stop (){
digitalWrite (PWMA, LOW);
}

void straight(){
  myservo.write(63);//63 is straight
}

void forward(){
  myservo.write(63);
  digitalWrite(PWMA, HIGH);
  digitalWrite(DIRA, HIGH);
}
void right(){
  digitalWrite(PWMA, HIGH);
  myservo.write(23);
  digitalWrite(DIRA, HIGH);
}
void left(){
  digitalWrite(PWMA, HIGH);
  myservo.write(103);
  digitalWrite(DIRA, HIGH);
}


void setup() {
  //delay (1000)=25 in 
  pinMode (DIRA, OUTPUT);
  pinMode (PWMA, OUTPUT);
  myservo.attach(6);
  straight();
  delay (5000);
  forward();
  delay (4724);
  right();
  delay (1900);
  forward();
  delay (4724);
  Stop();

}

void loop() {

}
