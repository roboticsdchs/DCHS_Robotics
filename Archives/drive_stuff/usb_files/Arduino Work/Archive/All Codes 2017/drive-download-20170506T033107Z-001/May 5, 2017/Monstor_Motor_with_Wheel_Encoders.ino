/*
  Right Motor Drive Pins: 8 & 7, Speed Pin: 6
  Right Encoder Pin: A5
  Left Motor Drive Pins: 4 & 9, Speed Pin: 5
  Left Encoder Pin: A3
  Steering Servo Pin: 10
  Distance Sensor Aiming Servo Pin: 11
  Front Distance Sensor Pin: A2
  Rear Distance Sensor Pin: A1
  Front Hall Effect Sensor Toggle Pin: 12
*/

//enables RedBot for use with encoders
#include <RedBot.h>
RedBotMotors motors;
RedBotEncoder encoder = RedBotEncoder(A3, A5);  // initializes encoders
int countsPerRev = 192;   // 4 pairs of N-S x 48:1 gearbox = 192 ticks per wheel rev
// variables used to store the left and right encoder counts.
int lCount;
int rCount;

//sets pins used for moters
int leftmotorForward = 4; // left motor (+) green wire
int leftmotorBackward = 9; // left motor (-) black wire
int leftmotorspeed = 5; // left motor speed signal
int rightmotorForward = 8; // right motor (+) green wire
int rightmotorBackward = 7; // right motor (-) black
int rightmotorspeed = 6; // right motor speed signal

void setup(){
  Serial.begin(9600);
  Serial.println("___________________________________");
  pinMode(leftmotorForward, OUTPUT);
  pinMode(leftmotorBackward, OUTPUT);
  pinMode(leftmotorspeed, OUTPUT);
  pinMode(rightmotorForward, OUTPUT);
  pinMode(rightmotorBackward, OUTPUT);
  pinMode(rightmotorspeed, OUTPUT);

}
void loop(){
  lCount = encoder.getTicks(LEFT);    // read the left motor encoder
  rCount = encoder.getTicks(RIGHT);   // read the right motor encoder
  Serial.print(lCount);
  Serial.print(",");
  Serial.println(rCount);
  digitalWrite(leftmotorBackward,LOW);
  digitalWrite(rightmotorBackward,LOW);
  digitalWrite(leftmotorForward,HIGH);
  digitalWrite(rightmotorForward,HIGH);
  analogWrite(leftmotorspeed, 25);
  analogWrite(rightmotorspeed, 40);

}

