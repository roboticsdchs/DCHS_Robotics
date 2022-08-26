int leftangle = 0;
int center = 13;
int rightangle = 26;
int TrueSpeed;
int Angle;
int moveport = 5;
int turnport = 6;
int ledPin = 3;
#include <Servo.h>

Servo turnmotor;
Servo movemotors;

//Alpha (or at least this one should be alpha test)
void setup() {
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  pinMode(3, OUTPUT);  
  turnmotor.write(center);
  Forward();
  delay(5000);
  Left();
  delay(3000);
  Forward();
  delay(2000);
  ReverseRight();
  delay(10000);
  turnmotor.write(center);  
  Forward();
  delay(5000);
  Stop();
  turnmotor.write(center);
  digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(5000);                  // waits for a second
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(500);                  // waits for a second
}



  void Forward() {
    TrueSpeed = 254;
    movemotors.write(110);
  }
  void Backward() {
    TrueSpeed = 127;
    movemotors.write(80);
  }

  void Stop() {
    movemotors.write(90);
  }
  void Left() {
    movemotors.write(110);
    turnmotor.write(leftangle);
    }

   void Right() {
    movemotors.write(110);
    turnmotor.write(rightangle);
   }

    void ReverseRight(){
      movemotors.write(80);
      turnmotor.write(rightangle);
    }


  void loop() {
    }
