
int pointed = 90; //pointed provides reference point for servo movement

int dir = 2;

#include <SPI.h>
#include <Pixy.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <RedBot.h>

/*
 * Sig 1 = red
 * sig 2=  blue
 * sig 3 = green
 */

RedBotEncoder encoder = RedBotEncoder(A3, A1);

//speed varibles

// This is the main Pixy object
Pixy pixy;


Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

int lCount = 0;

int leftmotorForward = 4;
int leftmotorBackward = 9;
int leftmotorspeed = 5;
int rightmotorForward = 8;
int rightmotorBackward = 7;
int rightmotorspeed = 6;

//float dir;
float heading;
//float pointed;
int angle = 90;

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pixy.init();

  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();

  delay(1000);

  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(10, OUTPUT);


}


void GoForward(int DTG){
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 50);
  analogWrite(rightmotorspeed, 50);
  while(lCount < DTG){
    lCount = encoder.getTicks(LEFT);
    angle_check();
    delay(50);
  }
   encoder.clearEnc(LEFT); //what's encoder?
  lCount = 0;
}

void angle_check(){
  ReadCompass();
  Serial.print(dir);
  Serial.print("---");
  Serial.println(heading);
  if ((heading + 3 < dir) && (angle < 120)){
    angle = angle + .5;
    servoPulse(angle);
  }
  else if ((heading - 3 > dir) && (angle > 60)){
    angle = angle - .5;
    servoPulse(angle);
  }
  else if((heading < dir + 3) && (heading > dir - 3)){
    servoPulse(90);
    Serial.print("-----------------------");
  }
}

void ReadCompass(){
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  if (heading < 0){
    heading = 360 + heading;
  }
}

void servoPulse (int pointed) // controls servo
{
  int pwm = (pointed * 11) + 500;    // Convert pointed to microseconds
  digitalWrite(10, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(10, LOW);
  delay(50);                   // Refresh cycle of servo
}


void loop()
{
  static int i = 0;
  int pos;
  int j;
  uint16_t blocks;
  char buf[32];
  int pwm = (pointed * 11) + 500;    // Makes PWM a Global Variable. See below for PWM definition
  // put your main code here, to run repeatedly:
  // servoPulse(pointed); //sets servo pointed to 90 degrees to equal pointed
  delay(5);

  // grab blocks!
  blocks = pixy.getBlocks();
  pos = pixy.blocks[j].x;
  // If there are detect blocks, print them!
  if (blocks)
  {
    if (i % 50 == 0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      //for (j = 0; j < blocks; j++)
      //   {
      Serial.print(pixy.blocks[j].width);
      Serial.print(" ");
      //        sprintf(buf, "  block %d: ", j);
      //        Serial.print(buf);
      //        pixy.blocks[j].print();
      //     }
      Serial.println();

      if (pixy.blocks[j].signature == 1) //If Pixy sees Signature 1, Go forward
      {
        digitalWrite(leftmotorBackward, LOW);
        digitalWrite(rightmotorBackward, LOW);
        digitalWrite(leftmotorForward, HIGH);
        digitalWrite(rightmotorForward, HIGH);
        analogWrite(leftmotorspeed, 40);
        analogWrite(rightmotorspeed, 40);       
      }
      if (pixy.blocks[j].signature == 2) //If pixy sees Signature 2, go backward
      {
        digitalWrite(leftmotorForward, LOW);
        digitalWrite(rightmotorForward, LOW);
        digitalWrite(leftmotorBackward, HIGH);
        digitalWrite(rightmotorBackward, HIGH);
        
        analogWrite(leftmotorspeed, 40);
        analogWrite(rightmotorspeed, 40);
      }
      if (pixy.blocks[j].signature == 3) //If pixy sees signature 3, Stop Everything
      {
        digitalWrite(leftmotorBackward, LOW);
        digitalWrite(rightmotorBackward, LOW);
        digitalWrite(leftmotorForward, LOW);
        digitalWrite(rightmotorForward, LOW);
        analogWrite(leftmotorspeed, 0);
        analogWrite(rightmotorspeed, 0);
      }
    }
  }
}


void turn(int turn_dir){
  if (turn_dir == 1){
    servoPulse(135);
    dir = dir + 90;
    
   // if (dir > 360){
     // dir = dir - 360;
    //}
    Serial.print(dir);
    Serial.print("---");
    Serial.println(heading);
//    while (heading < dir - 25){
//      ReadCompass();
//      servoPulse(125);
      if (heading > 0 && heading < 50 && dir > 360)
      {
        dir = dir - 360;
      }
      
      Serial.print(dir);
      Serial.print("---");
      Serial.println(heading);
    }
    servoPulse(90);
    delay(2000);
  
  if (turn_dir ==2)
  {
    servoPulse(55);
    dir = dir - 90;
    while(heading<dir + 25)
    {
      ReadCompass();
      servoPulse(125);
      if (heading < 360 && heading > 330 && dir <360)
      { 
        dir = dir - 360;
      }
      servoPulse(90);
    }
  }
}

