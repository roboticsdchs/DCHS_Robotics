int leftangle = 80;
int center = 88;
int rightangle = 95;
int TrueSpeed;
int Angle;
int moveport = 10;
int turnport = 9;
#include <Servo.h>

Servo turnmotor;
Servo movemotors;
void setup() {
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
  delay(5000);
 // Forward();
  Left();
  movemotors.write(90);
 
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


  void loop() {
    }
