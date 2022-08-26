
//This code is the start for sensing the lines in how there is supposed to be the following/sensing of the lines for task charlie: lane assist
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
int leftangle = 113;//for 45 degree angle minus 8
int center = 119;
int rightangle = 139; //for 45 degree angle plus 7
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
#include <Servo.h>
#include <Wire.h>
#include <Pixy2.h>

Servo turnmotor;
Servo movemotors;
Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  // we need to initialize the pixy object
  pixy.init();
  // Change to line tracking program

  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
}
void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(5);
}
void Backward() {
  TrueSpeed = 127;
  movemotors.write(70);
  delay(5);
}
void Stop() {
  TrueSpeed = 191;
  movemotors.write(90);
  delay(5);
}
void Left() {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(leftangle);
  delay(5);
  turnmotor.write(center);
}
void Right(int wait) {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(rightangle);
  delay(wait);
  turnmotor.write(center);
}
void loop()
{
  int8_t i;
  char buf[128];
  pixy.changeProg("line");

  pixy.line.getMainFeatures();
  //pixy.line.setMode(LINE_MODE_WHITE_LINE);
  if (pixy.line.numVectors == 0) {
    Serial.print("right");
    Right(30);
  }

  // print all vectors
  for (i = 0; i < pixy.line.numVectors; i++)
  {
    sprintf(buf, "line %d: ", i);
    Serial.print(buf);
    pixy.line.vectors[i].print();
  }
  for (i = 0; i < pixy.line.numVectors; i++) {
    //start here by having some sort of range so that the car can potentially veer and not go haywire on the steering - I start with five and then we can advance
    if (((pixy.line.vectors[i].m_x1 >= 39 && pixy.line.vectors[i].m_x1 < 39)&&pixy.line.vectors[i].m_x0 >= 58)||((pixy.line.vectors[i].m_x0 >= 39 && pixy.line.vectors[i].m_x0 <= 47)&&pixy.line.vectors[i].m_x1 >= 58)) {
      Serial.print("straight");
      Forward();
      //run the else if loop below if the car is to the right of the range, this should make it go to the left when operational and when it is way right
    } else if ((pixy.line.vectors[i].m_x1 >= 41 && pixy.line.vectors[i].m_x0 < 39) || (pixy.line.vectors[i].m_x0 >= 41 && pixy.line.vectors[i].m_x1 < 39)) {
      Serial.print("right");
      Right(5);
    } else if ((pixy.line.vectors[i].m_x0 >= 47 && pixy.line.vectors[i].m_x1 >= 47)) {
      
      Serial.print("left");
      Left();
    }
  }
  // print all intersections - not particularly useful for our purposes
  for (i = 0; i < pixy.line.numIntersections; i++)
  {
    sprintf(buf, "intersection %d: ", i);
    Serial.print(buf);
    pixy.line.intersections[i].print();
  }

}
