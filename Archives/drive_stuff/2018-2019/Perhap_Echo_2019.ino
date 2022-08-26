int ledPin = 7;
int sensorPin = A2;
int sensorValue = 0;
int TrueSpeed;

#include <Servo.h>
int driveport = 10;
int steerport = 9;
Servo driveservo;

void setup() {
  pinMode(10, OUTPUT); //motor
  driveservo.attach(steerport);
  pinMode(7, OUTPUT);
}

void Forward() {
  TrueSpeed = 254;
  analogWrite(10, 210);
  //delay(5000);
}

 void Stop() {
   TrueSpeed = 191;
   analogWrite(driveport, TrueSpeed);
   delay(5000);
  }



void loop() {
  // put your main code here, to run repeatedly:
   sensorValue = analogRead(sensorPin);

   while (sensorValue >= 200){
    Forward();
    sensorValue = analogRead(sensorPin);
   } if (sensorValue < 200){
    Stop();
   }
   sensorValue = analogRead(sensorPin);
   }
