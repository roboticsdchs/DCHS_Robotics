int leftangle = 80;
int center = 88;
int rightangle = 95;
int TrueSpeed;
int Angle;
#include <Servo.h>

Servo myservo;
void setup() {
  pinMode(9, OUTPUT); //motor
  myservo.attach(6);

}


void Forward() {
  TrueSpeed = 254;
  analogWrite(9, TrueSpeed);
  delay(5000);
}
void Backward() {
  TrueSpeed = 127;
  analogWrite(9, TrueSpeed);
  delay(5000);
}
  void Stop() {
    TrueSpeed = 191;
    analogWrite(9, TrueSpeed);
    delay(5000);
  }
  void Left() {
    TrueSpeed = 254;
    analogWrite(9, TrueSpeed);
    myservo.write(leftangle);
    delay(5000);
    myservo.write(center);
    }

    void Right() {
    TrueSpeed = 254;
    analogWrite(9, TrueSpeed);
    myservo.write(rightangle);
    delay(5000);
    myservo.write(center);
    }






  void loop() {
}
