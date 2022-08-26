//Drive straight 

#define CW  0

#define CCW 1



// Motor definitions to make life easier:

#define MOTOR_A 0

#define MOTOR_B 1



// Pin Assignments //

// Don't change these! These pins are statically defined by shield layout

const byte PWMA = 3;  // PWM control (speed) for motor A

const byte PWMB = 11; // PWM control (speed) for motor B

const byte DIRA = 12; // Direction control for motor A

const byte DIRB = 13; // Direction control for motor B



float heading; //The current heading of the car. GPIO input from compass

int dir = 90;     //the desired degree

int aspeed = 225; //speed of motor A or Right

int bspeed = 225; //speed of motor B or Left

int temp;     //A temporary variable

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);



void setup() 
{
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); 
  Serial.println("");
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a probblem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);

  }
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(10, OUTPUT);
}


void loop() 
{
  readCompass();

  if (heading > dir){
    while (heading > dir){
    readCompass();
    digitalWrite(9, HIGH);
    temp = heading - dir;
    temp = temp * 3;
    aspeed = aspeed - temp;
    bspeed = bspeed + temp;
     }
    aspeed = 255;
    bspeed = 255;


  }
  else if(dir > heading){
    while (dir > heading){
    readCompass();    //Reads Compass Function at bottom
    digitalWrite(2, HIGH);
    temp = dir - heading;
      temp = temp * 3;
      aspeed = aspeed + temp;
    bspeed = bspeed - temp;
    }
    aspeed = 255;
    bspeed = 255;

  }

  else if (dir == heading)
  {
    while (heading - 2 < dir < heading + 2){
    readCompass();
    digitalWrite(10, HIGH);
    aspeed = aspeed;
    bspeed = bspeed;

    }
  }
  if (aspeed < 75)
  {
    if (bspeed < 75)
    {
      fallout(); //when aspeed and bspeed are less than speed 75, it comences fallout void
    }
  }
  driveArdumoto(MOTOR_A, CW, aspeed);
  driveArdumoto(MOTOR_B, CW, bspeed);
    digitalWrite(10, LOW);
    digitalWrite(2, LOW);
    digitalWrite(9, LOW);    
}


void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

void setupArdumoto()
{
  // All pins should be setup as outputs:

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);

}

void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == aspeed)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == bspeed)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}   



void readCompass()
{
  /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  // Calculate the angle of the vector y,x
  heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  return;
}

void fallout ()
{
  aspeed = aspeed + 20;
  bspeed = bspeed + 20;
}


