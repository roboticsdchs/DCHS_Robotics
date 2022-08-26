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

#include <Pixy2.h>

Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  // we need to initialize the pixy object
  pixy.init();
  // Change to line tracking program
  pixy.changeProg("line");
}

void loop()
{
  int8_t i;
  char buf[128];
 
  pixy.line.getAllFeatures();

  // print all vectors
  for (i=0; i<pixy.line.numVectors; i++)
  {
    sprintf(buf, "line %d: ", i);
    Serial.print(buf);
    pixy.line.vectors[i].print();
  }
   for(i = 0; i<pixy.line.numVectors; i++){
    //start here by having some sort of range so that the car can potentially veer and not go haywire on the steering - I start with five and then we can advance
  if((pixy.line.vectors[i].m_x0>=18 && pixy.line.vectors[i].m_x0 <=23)||(pixy.line.vectors[i].m_x0 >= 56&& pixy.line.vectors[i].m_x0<=61)){
    Serial.print("in the zone");
    //run the else if loop below if the car is to the right of the range, this should make it go to the left when operational and when it is way right
    }else if ((pixy.line.vectors[i].m_x0 >23&&pixy.line.vectors[i].m_x0<=36)||pixy.line.vectors[i].m_x0 > 61){
      Serial.print("go to the left");
      }else if (pixy.line.vectors[i].m_x0<18||pixy.line.vectors[i].m_x0<56){
        Serial.print("go to the right");
        }
  }
  
  // print all intersections
  for (i=0; i<pixy.line.numIntersections; i++)
  {
    sprintf(buf, "intersection %d: ", i);
    Serial.print(buf);
    pixy.line.intersections[i].print();
  }
 
}
