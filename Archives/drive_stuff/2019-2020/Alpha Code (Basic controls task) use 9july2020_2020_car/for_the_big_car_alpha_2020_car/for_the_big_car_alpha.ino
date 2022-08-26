int leftangle = 78;
int center = 88;
int rightangle = 100;
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
  delay(5000);
  Forward();
  Right();  
  Forward();
  Stop();
  movemotors.write(90);
  turnmotor.write(center);
}


void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(5400);
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
    //movemotors.write(110);
    turnmotor.write(rightangle);
    delay(5000);
    turnmotor.write(center);
    }


  void loop() {
    }
