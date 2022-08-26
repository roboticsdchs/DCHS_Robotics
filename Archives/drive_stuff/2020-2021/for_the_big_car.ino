//#include <TinyGPS++.h>

#include <ArduinoSort.h>

#include <Pixy2.h>

#include <NewPing.h> 

#include <Servo.h>
int turnServoPort = 4;
int drivePort = 3;

int tBack = 23;//yellow
int eBack = 6;//blue
int tBRight = 27;//white
int eBRight = 7;//blue
int tFront = 25;//yellow
int eFront = 5;//white
int maxDist = 200;

NewPing sonarf(tFront, eFront, maxDist);
NewPing sonarb(tBack, eBack, maxDist);
NewPing sonarbr(tBRight, eBRight, maxDist);

Pixy2 pixy;

Servo turnServo;
void setup() {
  Serial.begin(115200);
  turnServo.attach(turnServoPort);
  pixy.init();
  Serial.print("lol");
  turn(8);
  //alpha();
  //bravo();
  //charlie();
  delta();
}
//driving capabilities
void alpha(){
  drive(5, 8, 5000);
  drive(5, -45, 2500);
  drive(5, 8, 5000);
  drive(0, 8, 5000);
}
//object avoidance
void bravo(){
  int start = millis();
  turn(8);
  motors(5);
  while(millis() - start < 15000 && findDist("f") > 50){
    turnInstant(8);
    delay(50);
  }
  int pause = millis();
  Serial.println("object found");
  motors(0);
  while(findDist("f") < 50){
    turnInstant(8);
    delay(50);
  }
  Serial.println("object removed");
  delay(2000);
  pause = millis() - pause;
  Serial.println(pause);
  while(millis() - (start + pause) < 15000){
    turnInstant(8);
    motors(5);
    delay(50);
  }
  motors(0);
}
//lane assist
void charlie(){
  turnInstant(8);
  
  int8_t mainLine;
  int lineDistance;
  pixy.changeProg("line");
  int start = millis();
  while(millis() - start < 100000){
    motors(3);
    mainLine = pixy.line.getMainFeatures();
    if(pixy.line.numVectors > 0){
      if(pixy.line.vectors[0].m_x0 > pixy.line.vectors[0].m_x1){
        lineDistance = pixy.line.vectors[0].m_y1;
      }
      else{
        lineDistance = pixy.line.vectors[0].m_y0;
      }
      Serial.println(lineDistance);
    }
    int turnAngle = map(lineDistance, 0, 40, 45, -45);
    turnInstant(turnAngle);
  }

}
//parrellel parking
void delta(){
  long start;
  long gap = 0;
  boolean space = true;
  boolean go = true;
  turnInstant(8);
  motors(3);
  while(go == true){
    int distance = findDist("br");
    Serial.println(distance);
    if(distance<70 && distance != 0){
      go = false;
      start = millis();
    }
  }
  go = true;
  //Find the spot
  while(go == true){
    turnInstant(8);
    int distance = findDist("br");
    Serial.println(distance);
    if(distance<70 && distance != 0){
        if(millis()-start > 3000){
          go = false;
        }
        start = millis();
    }
  }
  go = true;
  
  motors(0);
  turn(-45);
  motors(-3);
  
  while(go == true){
    int distance = findDist("b");
    Serial.println(distance);
    if(distance<100 && distance != 0){
      go = false;
    }
  }
  go = true;
  
  motors(0);
  turn(8);
  motors(-3);
  
  while(go == true){
    int distance = findDist("b");
    Serial.println(distance);
    if(distance<20 && distance != 0){
      go = false;
    }
  }

  motors(0);
}
//parking garage
void echo(){
  brightSignature = 1;
  darkSignature = 2;
  pixy.changeProg("color_connected_components");

  turn(8);
  motors(3);
  while(findDist("f") > 50){
    pixy.ccc.getBlocks();
    if(pixy.ccc.blocks[0].m_signature == brightSignature){
      
    }
    if(pixy.ccc.blocks[0].m_signature == darkSignature){
      
    }
  }
}
//GPS
void foxtrot(){
  
}
//following lead vehice
void golf(){
  int targetSignature = 3; //Color signature pixy looks for
  pixy.changeProg("color_connected_components");
  int objectPosition;
  int turnAngle;
  turn(8);
  //Should keep  x at 157.5                                                                                
  while(millis() < 50000){
    int index = 0;
    pixy.ccc.getBlocks();
    int objects = pixy.ccc.numBlocks;
    while(index < objects && pixy.ccc.blocks[index].m_signature != targetSignature){
      index++;
    }
    if(pixy.ccc.blocks[index].m_signature = targetSignature){
      objectPosition = pixy.ccc.blocks[index].m_x;
      turnAngle = map(objectPosition, 0, 315, -45, 45);
    }
  }
}

//Drive: -10,10  Angle: -45,45
void drive(float drive, int angle, int howLong){
  turnInstant(angle);
  motors(drive);
  delay(howLong);
  motors(0); 
}

//Angle: -45,45
void turn(int angle) {
  int turns = map(angle, -45, 45, 75, 100);
  turnServo.write(turns);
  delay(2000);
}
void turnInstant(int angle) {
  int turns = map(angle, -45, 45, 75, 100);
  turnServo.write(turns);
}

//Drive: -10,10
void motors(int drive) {
  if(drive > 0.1 || drive < -0.1){
    int forwards = map(drive, 10, -10, 127, 254);
    analogWrite(drivePort, forwards);
  }
  else{
    analogWrite(drivePort, 191);
  }
}

int findDist(String spot){
  if(spot == "f"){
    int front[5];
    for(int i = 0; i <5; i++){
      front[i] = sonarf.ping_cm();
      delay(25);
    }
    sortArray(front, 5);
    return front[2];
  }
  else if(spot == "b"){
    int back[5];
    for(int i = 0; i <5; i++){
      back[i] = sonarb.ping_cm();
      delay(25);
    }
    sortArray(back, 5);
    return back[2];
  }
  else if(spot == "br"){
    int backr[5];
    for(int i = 0; i <5; i++){
      backr[i] = sonarbr.ping_cm();
      delay(25);
    }
    sortArray(backr, 5);
    return backr[2];
  }
}



  void loop() {
    Serial.print("F:");
    Serial.print(findDist("f"));
    Serial.print("BR:");
    Serial.print(findDist("br"));
    Serial.print("B:");
    Serial.println(findDist("b"));
    delay(50);
}
