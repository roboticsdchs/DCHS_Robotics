int leftangle = 78;
int center = 86;
int rightangle = 93;
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
//  turnmotor.attach(turnport);
//  movemotors.attach(moveport);
//  turnmotor.write(center);
//  delay(5000);
//  Forward();
//  Right();
//  movemotors.write(90);
//  turnmotor.write(center);
  pinMode(trigPin, OUTPUT);
  pinMode(pin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}


void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(5000);
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

int findMedian() {
  int small = 500;
  for(int i = 0; i < 5; i++){
    int d = sensor();
    if(d < small){
      small= d;
    }
    delay(1);
  }
  return small;
//  int dists[] = {0,0,0,0,0,0,0,0,0,0};
//  for(int i =0; i<10; i++){
//    dists[i] = sensor();
//    delay(10);
//  }
//  int swaps = 0;
//  do{ swaps =0;
//  for(int i = 0; i<10; i++){
//    if(dists[i] > dists[i+1]){
//      int hold = dists[i+1];
//      dists[i+1] = dists[i];
//      dists[i] = hold;
//      swaps++;
//    }
//  }
//  }while(swaps != 0);
// // Serial.println(dists);
//  return dists[5];
  }
  void loop() {
    Serial.println(findMedian());
  }
