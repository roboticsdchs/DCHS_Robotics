int leftangle = 75;
int center = 89;
int rightangle = 105;
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;

int pin = 8;
const int trigPin = 6;
const int echoPin = 5;
long duration;
int distance;

#include <Servo.h>;

Servo turnmotor;
Servo movemotors;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(pin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);


  
  bravo();
  //movemotors.write(90);
  //turnmotor.write(center);
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
int sensor(){
  digitalWrite(pin, HIGH);
  //clears trig pin
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  //sets the trigpin in high state for 10 micro seconds
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //reads the echopin, return the soundwave travel time in microsecond
  duration = pulseIn(echoPin, HIGH);
  //calculating the distance
  distance = duration*0.034/2;
  //delay(10);
  return distance;
}

int findSmallest() {
  int small = 500;
  for(int i = 0; i < 5; i++){
    int d = sensor();
    if(d < small){
      small= d;
    }
    delay(1);
  }
  return small;
}
void loop() {
  //Serial.println(findMedian());
  //turnmotor.write(90);
}
void alpha() {

}

void bravo() {
  int startTime = millis();
  while(findSmallest()>150 && (millis()>startTime + 21000)){
    Forward();
  }
  Stop();
}
