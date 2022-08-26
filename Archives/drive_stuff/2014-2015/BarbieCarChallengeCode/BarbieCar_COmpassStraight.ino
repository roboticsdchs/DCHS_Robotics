/* Servo */
//#include <Servo.h> 
//Servo turnServo;  //create servo object to control a servo 

/* Compass */
#include <Average.h> //import Average library for compass initialization
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345); //compass object
const float Pi = 3.14159; //apparently the pi constant isn't built into Arduino
float compassStraight = 0.0; //this will hold what we decide as "straight"

/* Monster Motor Shield */
#define BRAKEVCC 0
#define CW   1 //Clockwise Arguement in motorGo
#define CCW  2 //Counterclockwise Arguement in motorGo
#define BRAKEGND 3
#define CS_THRESHOLD 100
int inApin[2] = {7, 4};
int inBpin[2] = {8, 9};
int pwmpin[2] = {5, 6};
unsigned long driveMotorPreviousMillis; //will store last time motor was updated
int driveMotorDelay; //how long to wait before updating the motor during manuver
byte turnServoDirection = 1; //0=left; 1=center; 2=right
int standardDriveSpeed = 50;
int standardTurnSpeed = 50;

/* Distance Sensors */
// FL = FrontLeft
    int FLDistSensorVal;          //value from the distance Front Left sensor
    const byte FLDistSensorPin = 2;   //Front Left sensor analog pin
    boolean FLDetect = false; //Front Left sensor detection
// FLC = FrontLeftCenter
    int FLCDistSensorVal;         //value from the distance Front Left sensor
    const byte FLCDistSensorPin = 3;   //Front Left Center sensor analog pin
    boolean FLCDetect = false; //Front Left Center sensor detection
// FRC = FrontRightCenter
    int FRCDistSensorVal;         //value from the distance Front Right sensor
    const byte FRCDistSensorPin = 10;   //Front Right Center sensor analog pin
    boolean FRCDetect = false; //Front Right Center sensor detection
// FR = FrontRight
    int FRDistSensorVal;          //value from the distance Front Right sensor
    const byte FRDistSensorPin = 11;   //Front Right sensor analog pin
    boolean FRDetect = false; //Front Right sensor detection
// BL = BackLeft
    int BLDistSensorVal;          //value from the distance Front Right sensor
    const byte BLDistSensorPin = 12;   //Back Left sensor analog pin
    boolean BLDetect = false; //Back Left sensor detection
// BR = BackRight
    int BRDistSensorVal;          //value from the distance Front Right sensor
    const byte BRDistSensorPin = 13;   //Back Right sensor analog pin
    boolean BRDetect = false; //Back Right sensor detection
int distThreshold = 50;     //threshold for the distance sensor

boolean delayOverride = false;

/* Color Sensor */
#include <Wire.h> //Remember to get the Library Downloaded
#include "Adafruit_TCS34725.h" //Another Part of the Library
#define commonAnode true //Absolutely Vital; No idea what it does
byte gammatable[256]; //See above comment
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X); //I^2C communications from sensor to board
int ColorSensorVal = 0; // 0=white/tarmac; 1=red; 2=green; 3=yellow;

void setup(){
    Serial.begin(9600); //start Serial
  
    /* Set Pins */
    pinMode(FLDistSensorPin, INPUT);
    pinMode(FLCDistSensorPin, INPUT);
    pinMode(FRCDistSensorPin, INPUT);
    pinMode(FRDistSensorPin, INPUT);
    pinMode(BLDistSensorPin, INPUT);
    pinMode(BRDistSensorPin, INPUT);
    for (int i=0; i<2; i++){
      pinMode(inApin[i], OUTPUT);
      pinMode(inBpin[i], OUTPUT);
      pinMode(pwmpin[i], OUTPUT);
    }
    
    /* Initilize */
    //drive motor
    for (int i=0; i<2; i++){ //initilize motors, not running
      digitalWrite(inApin[i], LOW);
      digitalWrite(inBpin[i], LOW);
    }
    //compass
    if(!mag.begin()){ //initilize compass
        //There was a problem detecting the LSM303 ... check your connections
        Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
        while(1); //stall forever
    }
    else{
        initCompass(); //initilize the compass; set the direction we will use as "straight"
    }
    //distance sensors
    FLDistSensorVal = readSensorRaw(FLDistSensorPin);
    FLCDistSensorVal = readSensorRaw(FLCDistSensorPin);
    FRCDistSensorVal = readSensorRaw(FRCDistSensorPin);
    FRDistSensorVal = readSensorRaw(FRDistSensorPin);
    BLDistSensorVal = readSensorRaw(BLDistSensorPin);
    BRDistSensorVal = readSensorRaw(BRDistSensorPin);
    
    //color sensor
    Serial.println("Color View Test!");
    if (tcs.begin()){
      Serial.println("Found sensor");
    }
    else{
      Serial.println("No TCS34725 found ... check your connections");
      while(1);
    }
    for (int i = 0; i < 256; i++){
      float x = i;
      x /= 255;
      x = pow(x, 2.5);
      x *= 255;
       if (commonAnode){
         gammatable[i] = 255 - x;
       }
       else{
         gammatable[i] = x;
       }
    }
}

void loop(){
    straightenCompass();
        forward(standardDriveSpeed);
    //main manuver logic
//    if((millis() - driveMotorPreviousMillis) > driveMotorDelay || delayOverride == true){ //only change if delay is done or overriding manuver 
//        delayOverride = false; //reset override flag, if any
//        driveMotorPreviousMillis = millis(); //set up for next delay
//        
//        if (driveMotorDelay > 0){ //code to run after a manuver is completed
//            //initCompass(); //reset the compass
//        }
//        
//        forward(standardDriveSpeed);
//        driveMotorDelay = 0;
//    }
    
}



/* Basic Manuver Functions */
void forward(int velocity){ //drive forward
    motorGo(0, CW, velocity);
    motorGo(1, CCW, velocity);
}

void backward(int velocity){ //drive backward
    //brake();
    //delay(50);
    motorGo(0, CCW, velocity);
    motorGo(1, CW, velocity);
}

void straight(){ //turn wheels straight
    turnServoDirection = 1;
}

void left(int velocity){ //turn wheels left
    motorGo(0, CCW, velocity);
    motorGo(1, CCW, velocity);
    turnServoDirection = 0;
}

void right(int velocity){ //turn wheels right
    motorGo(0, CW, velocity);
    motorGo(1, CW, velocity);
    turnServoDirection = 2;
}

void brake(){
    motorOff(0);
    motorOff(1);
}

/* Advanced Manuver Functions */
void search(){ //searches for a direction to drive
    brake();
    
    //check left
    float turnDeviation = -45; //how far to turn in degrees
    left(standardTurnSpeed); //turn left at half speed
    while(calculateCompassDeviation() > turnDeviation){ 
        delay(25); //wait a little and check again
    }
    brake(); //stop, hammer time
    readDistSensors();
    if(FLDetect==false || FLCDetect==false || FRCDetect==false ){ 
        initCompass();
        resetDistSensorFlags();
        return;
    }
    
    //check right
    turnDeviation = 45; //how far to turn in degrees
    right(standardTurnSpeed); //turn left at half speed
    while(calculateCompassDeviation() < turnDeviation){ 
        delay(25); //wait a little and check again
    }
    brake();
    readDistSensors();
    if(FLCDetect==false || FRCDetect==false || FRDetect==false ){ 
        initCompass();
        resetDistSensorFlags();
        return;
    }
    
    //back up and try again
    turnDeviation = 0; //how far to turn in degrees
    left(standardTurnSpeed); //turn left at half speed
    while(calculateCompassDeviation() > turnDeviation){ 
        delay(25); //wait a little and check again
    }
    brake();
    backward(standardTurnSpeed);
    delay(250);
    search();
}

/* Compass Functions */
void initCompass(){ //initilize the compass; set the direction we will use as "straight"
    Average<float> ave(5);
    for(byte x=0; x<5; x++){ //take five samples
       ave.push(getCompass());
    }
    compassStraight = ave.mean(); //average the samples and use as "straight"
    Serial.print("Initial Compass Average (will use as straight):");
    Serial.println(compassStraight);
}

float getCompass(){ //read from the compass, convert to 360 degrees, and return as float
    if(!mag.begin()){ //initilize compass
        //There was a problem detecting the LSM303 ... check your connections
        Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    }
    //Get a new sensor event
    sensors_event_t event; 
    mag.getEvent(&event);
    
    //Calculate the angle of the vector y,x
    float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
    
    //Normalize to 0-360
    if (heading < 0){
        heading = 360 + heading;
    }
    Serial.print("Compass Facing: ");
    Serial.println(heading);
    return heading;
}

float calculateCompassDeviation(){ //calculate the compass's surrent deviation from compassStraight
    float compassCurrentDirection  = getCompass(); //get current direction
    float diff = compassCurrentDirection - compassStraight; //find the difference between the current direction and "straight"
    //correct for overflowing
    if (diff > 180){
        diff = diff - 360; //for angles > 180, correct in the opposite direction.
    }
    else if (diff < -180){
        diff = diff + 360; //for angles < -180, correct in the opposite direction.
    }
    return diff; //positive is right, negative is left
}

void straightenCompass(){ //determine if car is not straight and turn if necessary
    float compassTolerance = 3.0; //set compass deviation tolerance in degrees
    
    float diff = calculateCompassDeviation();
    
    if (diff > compassTolerance){ //too far right, turn left
        left(standardTurnSpeed);
        delay(250);
    }
    else if (diff < -compassTolerance){ //too far left, turn right
        right(standardTurnSpeed);
        delay(250);
    }
    else{ //straight enough
        straight();
    }
}

/* Distance Sensor Functions */
long readSensorRaw(byte pwPin){
    return (pulseIn(pwPin, HIGH)/147)*2.54;
}

long readSensorCorrected(byte pwPin, long pulse){
    int pulsetemp = 0;
    pulsetemp = readSensorRaw(pwPin);
    while(pulsetemp<sqrt(pulse)){
        delayMicroseconds(50);
        pulsetemp = readSensorRaw(pwPin);
    }
    return pulsetemp;
}

void readDistSensors(){
    //read sensors
    FLDistSensorVal = readSensorCorrected(FLDistSensorPin, FLDistSensorVal);
    FLCDistSensorVal = readSensorCorrected(FLCDistSensorPin, FLCDistSensorVal);
    FRCDistSensorVal = readSensorCorrected(FRCDistSensorPin, FRCDistSensorVal);
    FRDistSensorVal = readSensorCorrected(FRDistSensorPin, FRDistSensorVal);
    BLDistSensorVal = readSensorCorrected(BLDistSensorPin, BLDistSensorVal);
    BRDistSensorVal = readSensorCorrected(BRDistSensorPin, BRDistSensorVal);
    //print distence 
    Serial.print('a');
    Serial.println(FLDistSensorVal);
    Serial.print('b');
    Serial.println(FLCDistSensorVal);
    Serial.print('c');
    Serial.println(FRCDistSensorVal);
    Serial.print('d');
    Serial.println(FRDistSensorVal);
    Serial.print('e');
    Serial.println(BLDistSensorVal);
    Serial.print('f');
    Serial.println(BRDistSensorVal);
    Serial.println("--");
}

void detectDistSensors(){
    if(FLDistSensorVal < distThreshold){FLDetect=true;}
    if(FLCDistSensorVal < distThreshold){FLCDetect=true;}
    if(FRCDistSensorVal < distThreshold){FRCDetect=true;}
    if(FRDistSensorVal < distThreshold){FRDetect=true;}
    if(BLDistSensorVal < distThreshold){BLDetect=true;}
    if(BRDistSensorVal < distThreshold){BRDetect=true;}
}

void resetDistSensorFlags(){
    FLDetect=false;
    FLCDetect=false;
    FRCDetect=false;
    FRDetect=false;
    BLDetect=false;
    BRDetect=false;  
}

/* Motor Control Funtions */
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1) //Only 2 pins on sheild (Read as "0" and "1"). Makes sure you didn't invent a third one
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm); // Speed/Strength/Power of motor (? to 1023)
    }
  }
}

void motorOff(int motor) //Choose the motor to turn off, 0 or 1.
{
  // Initialize braked
  for (int i=0; i<2; i++)//This just turns EVERYTHING off.
  {
    digitalWrite(inApin[i], LOW);
    digitalWrite(inBpin[i], LOW);
  }
  analogWrite(pwmpin[motor], 0);
}

int readColorSensor(){ //Reads Color Sensor, Returns a Number for Color Value; See guide at library inclusions
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);
  //delay(50);
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  //Serial.println("RED RED RED RED RED RED"); //Use this code to get raw RGB values
  //Serial.println(r);
  //Serial.println("GREEN GREEN GREEN GREEN");
  //Serial.println(g);
  //Serial.println("BLUE BLUE BLUE BLUE BLUE");
  //Serial.println(b);
  if ((r / g) >=1.00 && (r/g)<=1.6 && (r / b)>=1.3 && (r / b)<=2.3){ //WHITE-TOP
    //Serial.println("WhiteTop/////*****");
    ColorSensorVal = 0;
    return ColorSensorVal;
  }
  if(r<110 && g<90 && b<90){ //(r/g) >=0.80 && (r/b)>=1.0 && (r/g)<=1.0 && (r/b)<=1.3 //DARK TARMAC
    //Serial.println("REALIGN NEEDED===========================");
    ColorSensorVal = 0;
    return ColorSensorVal;
}
  else{ //If its not off the track. May need logic edit.
   if ((r / g) >= 2.3 && (r / b) >= 2.3){ //RED
    //Serial.println("RED/////######");
    ColorSensorVal = 1;
    return ColorSensorVal;
  }
   if ((r / g) <= 0.80 && (g/b) >= 2.00 ){  //(g / b) >= 1.15 //(r / b)<=1.2 //GREEN
    //Serial.println("GREEN/////&&&&&");
    ColorSensorVal = 2;
    return ColorSensorVal;
  }
  if ((r / g) >= 0.9 && (r / g) <=1.7 && (r/b)>=2.5 && (r / b) <= 3.8){ //(r/g)<=2.20 //YELLOW
    //Serial.println("YELLOW/////@@@@@");
    ColorSensorVal = 3;
    return ColorSensorVal;
  }
  }
}
