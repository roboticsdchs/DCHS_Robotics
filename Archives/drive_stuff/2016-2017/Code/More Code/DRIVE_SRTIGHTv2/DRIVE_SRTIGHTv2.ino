#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <RedBot.h>

#include <SPI.h>
#include <Pixy.h>


//speed varibles 

// This is the main Pixy object
Pixy pixy;

RedBotEncoder encoder = RedBotEncoder(A3, A1);

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

int lCount = 0;

int leftmotorForward = 4;
int leftmotorBackward = 9;
int leftmotorspeed = 5;
int rightmotorForward = 8;
int rightmotorBackward = 7;
int rightmotorspeed = 6;

float dir;
float heading;
float angle;

void setup(void) {
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  if (!mag.begin()) {
    Serial.println("ERROR: LSM303");
    while (1);
  }
  
  pixy.init();

  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();

//  ReadCompass();
  dir = heading;
  angle = 90;
  servoPulse(angle);
  delay(5000);
  pinMode(leftmotorForward, OUTPUT);
  pinMode(leftmotorBackward, OUTPUT);
  pinMode(leftmotorspeed, OUTPUT);
  pinMode(rightmotorForward, OUTPUT);
  pinMode(rightmotorBackward, OUTPUT);
  pinMode(rightmotorspeed, OUTPUT);
}

void ReadCompass() {
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  if (heading < 0) 
  {
    heading = 360 + heading;
  }
}

void servoPulse(int angle) {
  int pwm = ((angle * 11) + 500);
  digitalWrite(10, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(10, LOW);
  delay(10);
}


void GoForward(int DTG) {
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 70);
  analogWrite(rightmotorspeed, 70);
  while (lCount < DTG) {
    lCount = encoder.getTicks(LEFT);
    angle_check();
    delay(50);
  }
  encoder.clearEnc(LEFT);
  lCount = 0;
}

void angle_check() {
  ReadCompass();
  if ((heading + 3 < dir) && (angle < 120)) {
    angle = angle + .7;
    servoPulse(angle);
  }
  else if ((heading - 3 > dir) && (angle > 60)) {
    angle = angle - .7;
    servoPulse(angle);
  }
  else if ((heading < dir + 3) && (heading > dir - 3)) {
    angle = 90;
    servoPulse(angle);
  }
  Serial.print(dir);
  Serial.print("---");
  Serial.println(heading);
}


void loop(void) {
//  GoForward(750);
  servoPulse(90);
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 0);
  analogWrite(rightmotorspeed, 0);
  delay(9999999);
//  turn(1);
  
  static int i = 0;
  int pos;
  int j;
  uint16_t blocks;
  char buf[32];
  int pwm = (heading * 11) + 500;    // Makes PWM a Global Variable. See below for PWM definition

  // put your main code here, to run repeatedly:
 // servoPulse(heading); //sets servo angle to 90 degrees to equal heading
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
      {
        Serial.print(pixy.blocks[0].x );
        Serial.print(" ");
        //        sprintf(buf, "  block %d: ", j);
        //        Serial.print(buf);
        //        pixy.blocks[j].print();
      }
      Serial.println();
  if(pixy.blocks[j].signature = 1)
{
  GoForward(750);
}
if(pixy.blocks[j].signature = 2)
{
  GoForward(0);
}
}
  }
}
//

