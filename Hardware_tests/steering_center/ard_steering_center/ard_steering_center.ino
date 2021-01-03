int leftangle = 82;
int center = 99;
int rightangle = 114;
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
#include <Servo.h>

Servo turnmotor;
Servo movemotors;
void setup() {
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
  delay(1000);
  movemotors.write(110);
  turnmotor.write(center);
  delay(3000);
  movemotors.write(90);
  
  
}


void loop() {
}
