int leftangle = 38;
int center = 89;
int rightangle = 105;
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
const int trigPin0 = 2;
const int echoPin0 = 3;
const int trigPin1 = 4;
const int echoPin1 = 5;
long duration0;
int distance0;
long duration1;
int distance1;
#include <Servo.h>;

Servo turnmotor;
Servo movemotors;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
  while(distance1 < 20){
    Backward();
    }
  Right();
  Backward();
  delay(2000);
  while(distance >5){
    Left();
    
    
    }
    Stop();
    //parked light on
}

void loop() {

}
void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  //delay(5000);
}
void Backward() {
  TrueSpeed = 127;
  movemotors.write(70);
  delay(5000);
}
void Stop() {
  TrueSpeed = 191;
  movemotors.write(90);
  delay(5000);
}
void Left() {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(leftangle);
  delay(5000);
  turnmotor.write(center);
  }
void Right() {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(rightangle);
  delay(5000);
  turnmotor.write(center);
}
