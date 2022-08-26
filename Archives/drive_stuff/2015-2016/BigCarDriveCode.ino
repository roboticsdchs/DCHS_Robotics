// motor 0: 5,7,8
// motor 1: 6,4,9

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
 
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

//speed varibles 
int aspeed = 127;
int bspeed = 127;
int motorSpeedA = 0;
int motorSpeedB = 0;
int forwardSpeed = 33;
int adir = 1;
int bdir = 1;

//heading varibles
float heading;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
double error;

//Specify the links and initial tuning parameters
double Kp=1, Ki=0, Kd=0;
//PID loop vars
unsigned long lastTime = 0;
unsigned long SampleTime = 100;
double lastInput;
double ITerm;

//Output min max (set to motor speed) (still pid vars)
int outMax =  10;
int outMin = -10;

//turn vars
int setpointChanged = 0;

//hall effect vars
const int hallPinLeft = 12; // hall effect sensor 2
int hallStateLeft = 0; // "Button" variable #1 for left wheel
int HSRL; // "Button" variable #2 for left wheel
float hallLeftCounter = 0; // State change counter for left wheel
float HLC1 = 0; // Distance covered by left wheel

void setup(){
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  setupCompass(); //set initial PID vals
  
  pinMode(hallPinLeft, INPUT);
  HSRL = digitalRead(hallPinLeft);
}

void loop(){
  driveStraight(300);
  stopEverything(1000);
}

void driveMonsterA(byte dir, byte spd){
  analogWrite(5, spd);
  if (dir == 1){
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
  }
  else if (dir == 0){
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
  }
}

void driveMonsterB(byte dir, byte spd){
  analogWrite(6, spd);
  if (dir == 1){
    digitalWrite(4, HIGH);
    digitalWrite(9, LOW);
  }
  else if (dir == 0){
    digitalWrite(4, LOW);
    digitalWrite(9, HIGH);
  }
}

void readCompass() {
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
  
  
}

void PIDCompute(){
  unsigned long now = millis();
  unsigned long timeChange = (now - lastTime);
  if (timeChange>=SampleTime){
    //compute error
    error = Setpoint - Input;
    
    //adjust for the rollover
    if (error > 180){
      error-=360;
    }
    else if (error < -180){
      error+=360;
    }
    
    ITerm += (Ki * error);
    if (ITerm > outMax){
      ITerm = outMax;
    }
    else if (ITerm < outMin){
      ITerm = outMin;
    }
    
    //compute output
    Output = Kp * error + ITerm;
    
    if(Output > outMax){
      Output = outMax;
    }
    else if (Output < outMin){
      Output = outMin; 
    }
    
    //remember stuff for next time
    lastInput = Input;
    lastTime = now;
    
    //Serial.print(Setpoint); Serial.print("  "); Serial.print(Input); Serial.print("  "); Serial.print(error); Serial.print("  "); Serial.print(Output);Serial.print("  ");Serial.print(aspeed);Serial.print("  ");Serial.println(bspeed);
  }
}

void setupCompass(){
  readCompass();
  Input = heading;
  Setpoint = heading;
}

void turnRight(){
  motorSpeedA = 33;
  motorSpeedB = -33;
  if (setpointChanged == 0){
    Setpoint += 90;
    if(Setpoint > 360){
     Setpoint = Setpoint - 360;
    }
    setpointChanged = 1; 
  }
  while (Input < Setpoint-10){
    driveMotors();
  }
}

void turnLeft(){
  motorSpeedA = -33;
  motorSpeedB = 33;
  if (setpointChanged == 0){
    Setpoint -= 90;
    if(Setpoint < 0){
     Setpoint = Setpoint + 360;
    }
    setpointChanged = 1; 
  }
  while (Input > Setpoint+10){
    driveMotors();
  }
}

void driveStraight(int distance){
  hallLeftCounter = 0;
  motorSpeedA = forwardSpeed;
  motorSpeedB = forwardSpeed;
  setpointChanged = 0;
  while (HLC1 < distance){
    countLeft();
    driveMotors();
  }
}

void driveMotors(){
  readCompass();
  Input = heading;
  PIDCompute();
  aspeed = motorSpeedA + Output;
  bspeed = motorSpeedB - Output;
  if (aspeed < 0){
    aspeed = -aspeed;
    adir = 0;
  }
  else{
    adir = 1;
  }

  if (bspeed < 0){
    bspeed = -bspeed;
    bdir = 0;
  }
  else{
    bdir = 1;
  }
    
  driveMonsterA(adir, aspeed);  // Motor A at speed.
  driveMonsterB(bdir, bspeed);  // Motor B at quarter speed.
}

void stopEverything(int duration){
  motorSpeedA = 0;
  motorSpeedB = 0;
  digitalWrite(4,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(duration); //change this to something better later
}

void countLeft(){
   hallStateLeft = digitalRead(hallPinLeft);
   if (hallStateLeft != HSRL) {
    if (hallStateLeft == LOW) {
      hallLeftCounter++;
      HLC1 = ((hallLeftCounter / 16) * 89);
      Serial.print("   Left Distance: ");
      Serial.println(HLC1);
    }
   } 
}
