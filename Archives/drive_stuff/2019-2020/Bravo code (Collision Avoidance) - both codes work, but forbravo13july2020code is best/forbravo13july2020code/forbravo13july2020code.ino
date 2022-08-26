int leftangle = 108;//for 45 degree angle minus 8
int center = 127;
int rightangle = 139; //for 45 degree angle plus 7
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
int pin = 8;
const int trigPin = 3;
const int echoPin = 2;
long duration;
int distance;
long totalTime = 0;
int movestate = 0;
#include <Servo.h>

Servo turnmotor;
Servo movemotors;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
  bravo();
}

void loop() {
  // put your main code here, to run repeatedly:

}
void bravo() {
 long startTime = millis();
  long interTime = millis();
 while(movestate==0){
  while (findSmallest() > 150 && (totalTime < startTime + 21000)) {
   Backward();
  }
  while (findSmallest() < 150 && (totalTime < startTime + 21000)) {
    totalTime = totalTime + (millis()-interTime);
    interTime = millis();
    Serial.println(totalTime);
    Stop();
  }
   if (totalTime >= startTime + 30000) {
    movestate == 1;
    Stop();
  }
 }
 
}
void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(5);
}
void Backward() {
  TrueSpeed = 127;
  movemotors.write(70);
  delay(5);
}
void Stop() {
  TrueSpeed = 191;
  movemotors.write(90);
  delay(5);
}
void Left() {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(leftangle);
  delay(5);
  turnmotor.write(center);
}
void Right() {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(rightangle);
  delay(5);
  turnmotor.write(center);
}
int sensor() {
  digitalWrite(pin, HIGH);
  //clears trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //sets the trigpin in high state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //reads the echopin, return the soundwave travel time in microsecond
  duration = pulseIn(echoPin, HIGH);
  //calculating the distance
  distance = duration * 0.034 / 2;
  //delay(10);
  return distance;
}

int findSmallest() {
  int small = 500;
  for (int i = 0; i < 5; i++) {
    int d = sensor();
    if (d < small) {
      small = d;
    }
    delay(1);
  }
  return small;
}
