int backSensor = A5;
int sensorPin = A2;

int sensorValue = 0;
int backSensorValue = 0;
int TrueSpeed;

#include <Servo.h>
int driveport = 10;
int steerport = 9;
Servo driveservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(10, OUTPUT); //motor
  driveservo.attach(steerport);

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
  backSensorValue = analogRead(backSensor);
   Serial.println(sensorValue);

 while (sensorValue >= 150){
    Forward();
    sensorValue = analogRead(sensorPin);
    backSensorValue = analogRead(backSensor);
 }

 if (sensorValue < 150 && backSensorValue < 150){
  Stop();
  sensorValue = analogRead(sensorPin);
  backSensorValue = analogRead(backSensor);
 }
 }
 

}
