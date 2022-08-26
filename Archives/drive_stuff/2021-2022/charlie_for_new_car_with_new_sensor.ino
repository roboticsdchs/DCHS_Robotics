#include "Adafruit_VL53L1X.h"

#include <ArduinoSort.h>

#define IRQ_PIN 2
#define XSHUT_PIN 3

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

int leftangle = 0;
int center = 13;
int rightangle = 26;
int TrueSpeed;
int Angle;
int moveport = 10;
int turnport = 11;
int ledPin = 9;
#include <Servo.h>

Servo turnmotor;
Servo movemotors;

void setup() {
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  pinMode(3, OUTPUT);  
  turnmotor.write(center);
  
  Serial.begin(115200);
  while (!Serial) delay(10);

  Wire.begin();
  if (! vl53.begin(0x29, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(vl53.sensorID(), HEX);

  if (! vl53.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(vl53.vl_status);
    while (1)       delay(10);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  vl53.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(vl53.getTimingBudget());
  charlie();
}

void loop() {

}
void charlie(){
  turnmotor.write(center);
  Forward();
  while(findDist("f") < 500){
    Serial.println("object found");
    turnmotor.write(center);
    Stop();
    delay(5);
  }
  while(findDist("f") > 500) {
    Serial.println("no object");
    turnmotor.write(center);
    Forward();
  } 
  charlie();
}

int findDist(String spot){
  if(spot == "f"){
    int front[5];
    for(int i = 0; i <5; i++){
      front[i] = vl53.distance();
      vl53.clearInterrupt();
      delay(25);
    }
    sortArray(front, 5);
    return front[2];
  }
  else if(spot == "b"){
    int back[5];
    for(int i = 0; i <5; i++){
      back[i] = vl53.distance();
      vl53.clearInterrupt();
      delay(25);
    }
    sortArray(back, 5);
    return back[2];
  }
  else if(spot == "br"){
    int backr[5];
    for(int i = 0; i <5; i++){
      backr[i] = vl53.distance();
      vl53.clearInterrupt();
      delay(25);
    }
    sortArray(backr, 5);
    return backr[2];
  }
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
  TrueSpeed = 191;
  movemotors.write(90);
}
void Left() {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(leftangle);
  }

void Right() {
TrueSpeed = 254;
movemotors.write(110);
turnmotor.write(rightangle);
}
