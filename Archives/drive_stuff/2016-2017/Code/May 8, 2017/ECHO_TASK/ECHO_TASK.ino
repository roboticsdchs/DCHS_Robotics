#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <RedBot.h>

RedBotEncoder encoder = RedBotEncoder(A3, A1);

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

int lCount = 0;

int leftmotorForward = 4;
int leftmotorBackward = 9;
int leftmotorspeed = 5;
int rightmotorForward = 8;
int rightmotorBackward = 7;
int rightmotorspeed = 6;

int side_dis = A4;

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
  ReadCompass();
  dir = heading;
  angle = 90;
  servoPulse(angle);
  pinMode(leftmotorForward, OUTPUT);
  pinMode(leftmotorBackward, OUTPUT);
  pinMode(leftmotorspeed, OUTPUT);
  pinMode(rightmotorForward, OUTPUT);
  pinMode(rightmotorBackward, OUTPUT);
  pinMode(rightmotorspeed, OUTPUT);
}

void loop(void) {
  servoPulse(135);
  delay(1000);
  
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 30);
  analogWrite(rightmotorspeed, 30);
  //int sensor_value = analogRead(side_dis);
  //Serial.println(sensor_value);
  //while (sensor_value > 10) {
   // Serial.println(sensor_value);
    //sensor_value = analogRead(side_dis);
    //angle_check();
  //}
  //digitalWrite(leftmotorForward, LOW);
  //digitalWrite(rightmotorForward, LOW);
  //digitalWrite(leftmotorBackward, HIGH);
  //digitalWrite(rightmotorBackward, HIGH);
  //analogWrite(leftmotorspeed, 20);
  //analogWrite(rightmotorspeed, 20);
  //delay(200);
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 0);
  analogWrite(rightmotorspeed, 0);
  delay(500);
  servoPulse(135);
  Serial.println("155");
  digitalWrite(leftmotorForward, LOW);
  digitalWrite(rightmotorForward, LOW);
  digitalWrite(leftmotorBackward, HIGH);
  digitalWrite(rightmotorBackward, HIGH);
  analogWrite(leftmotorspeed, 50);
  analogWrite(rightmotorspeed, 50);
  delay(4000);
  digitalWrite(leftmotorForward, LOW);
  digitalWrite(rightmotorForward, LOW);
  digitalWrite(leftmotorBackward, HIGH);
  digitalWrite(rightmotorBackward, HIGH);
  analogWrite(leftmotorspeed, 0);
  analogWrite(rightmotorspeed, 0);
  servoPulse(55);
  Serial.println("55");
  digitalWrite(leftmotorForward, LOW);
  digitalWrite(rightmotorForward, LOW);
  digitalWrite(leftmotorBackward, HIGH);
  digitalWrite(rightmotorBackward, HIGH);
  analogWrite(leftmotorspeed, 50);
  analogWrite(rightmotorspeed, 50);
  delay(4000);
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 0);
  analogWrite(rightmotorspeed, 0);
  servoPulse(145);
  Serial.println("145");
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 50);
  analogWrite(rightmotorspeed, 50);
  delay(2000);
  servoPulse(90);
  Serial.println("90");
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 0);
  analogWrite(rightmotorspeed, 0);
  delay(9999999);
}

void ReadCompass() {
  sensors_event_t event;
  mag.getEvent(&event);
  float Pi = 3.14159;
  heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  if (heading < 0) {
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

void turn(int turn_dir){
  if (turn_dir == 1){
    servoPulse(145);
    dir = dir + 90;
    while (heading < dir - 25){
      ReadCompass();
      servoPulse(125);
      if (heading > 0 && heading < 50 && dir > 360)
      {
        dir = dir - 360;
      }
      
    }
    servoPulse(90);
    
  }
  if(turn_dir == 2){
    servoPulse(55);
    dir = dir - 90;
    while(heading<dir + 25){
      ReadCompass();
      servoPulse(125);
      if (heading < 360 && heading > 330 && dir < 360){
        dir = dir - 360;
      }
    }
    servoPulse(90);
  }
}

void GoForward(int DTG) {
  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 50);
  analogWrite(rightmotorspeed, 50);
  int sensor_value = analogRead(side_dis);
  while (sensor_value > 30) {
    sensor_value = analogRead(side_dis);
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
}

