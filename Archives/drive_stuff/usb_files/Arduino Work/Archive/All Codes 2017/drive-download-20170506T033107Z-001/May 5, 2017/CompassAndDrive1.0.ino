/*
  Right Motor Drive Pins: 8 & 7, Speed Pin: 6
  Right Encoder Pin: A5
  Left Motor Drive Pins: 4 & 9, Speed Pin: 5
  Left Encoder Pin: A3
  Steering Servo Pin: 10
  Distance Sensor Aiming Servo Pin: 11
  Front Distance Sensor Pin: A2
  Rear Distance Sensor Pin: A1
  Front Hall Effect Sensor Toggle Pin: 12
*/
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

int  dir;
int heading;
int angle;

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

//enables RedBot for use with encoders
#include <RedBot.h>
RedBotMotors motors;
RedBotEncoder encoder = RedBotEncoder(A3, A5);  // initializes encoders
int countsPerRev = 192;   // 4 pairs of N-S x 48:1 gearbox = 192 ticks per wheel rev
// variables used to store the left and right encoder counts.
int lCount;
int rCount;

//sets pins used for moters
int leftmotorForward = 4; // left motor (+) green wire
int leftmotorBackward = 9; // left motor (-) black wire
int leftmotorspeed = 5; // left motor speed signal
int rightmotorForward = 8; // right motor (+) green wire
int rightmotorBackward = 7; // right motor (-) black
int rightmotorspeed = 6; // right motor speed signal


void setup(){
  Serial.begin(9600);
  Serial.println("___________________________________");
  pinMode(leftmotorForward, OUTPUT);
  pinMode(leftmotorBackward, OUTPUT);
  pinMode(leftmotorspeed, OUTPUT);
  pinMode(rightmotorForward, OUTPUT);
  pinMode(rightmotorBackward, OUTPUT);
  pinMode(rightmotorspeed, OUTPUT);

  pinMode(10, OUTPUT);
  
  Serial.println("Magnetometer Test"); Serial.println("");
  
  heading = ReadCompass;
  dir = heading;
  angle = 90;
  servoPulse(90);
  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1);
}
}
void loop(){
  heading = ReadCompass;
  lCount = encoder.getTicks(LEFT);    // read the left motor encoder
  rCount = encoder.getTicks(RIGHT);   // read the right motor encoder
  Serial.print(lCount);
  Serial.print(",");
  Serial.println(rCount);
  digitalWrite(leftmotorBackward,LOW);
  digitalWrite(rightmotorBackward,LOW);
  digitalWrite(leftmotorForward,HIGH);
  digitalWrite(rightmotorForward,HIGH);
  analogWrite(leftmotorspeed, 40);
  analogWrite(rightmotorspeed, 40);

  ReadCompass();

  if (heading < 0)
  {
    heading = 360 + heading; //Take this out to disable 0 to 360 wrap. Replaced with 180, -180 wrap.
  }

  Serial.print("Compass heading: ");
  Serial.println(heading);
  delay(500);
  
  if (heading < dir)
  {
    angle = angle + 5;
    servoPulse(angle);
  }
  if (heading > dir)
  {
    angle = angle - 5;
    servoPulse(angle);
  }
}

void ReadCompass()  //This retreives data from the compass about where it's pointed
{
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;

  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;

}

void servoPulse (int angle) // controls servo
{
  int pwm = (angle * 11) + 500;    // Convert angle to microseconds
  digitalWrite(10, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(10, LOW);
  delay(50);                   // Refresh cycle of servo
}

