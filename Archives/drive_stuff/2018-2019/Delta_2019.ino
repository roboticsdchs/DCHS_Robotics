int leftangle = 80;
int center = 88;
int rightangle = 95;
int TrueSpeed;
int Angle;
#include <Servo.h>
int driveport = 10;
int steerport = 9;
Servo driveservo;
int t1Pin = 11;
int e1Pin = 12;
int t2Pin = 1;
int e2Pin = 2;

long duration1, cm1;
long duration2, cm2;


void setup() {
 pinMode(10, OUTPUT); //motor
  driveservo.attach(steerport);
   pinMode(t1Pin, OUTPUT);
   pinMode(t2Pin, OUTPUT);
   pinMode(t3Pin, OUTPUT);
   pinMode(e1Pin, INPUT);
   pinMode(e2Pin, INPUT);
   pinMode(e3Pin, INPUT);
   

}

void Forward() {
  TrueSpeed = 254;
  analogWrite(10, 210);
  //delay(5000);
}
void Backward() {
  TrueSpeed = 127;
  analogWrite(driveport, TrueSpeed);
  delay(5000);
}
  void Stop() {
    TrueSpeed = 191;
    analogWrite(driveport, TrueSpeed);
    delay(5000);
  }
  void Left() {
    TrueSpeed = 220;
    analogWrite(driveport, TrueSpeed);
    driveservo.write(leftangle);
    delay(5000);
    driveservo.write(center);
    }

    void backLeft() {
    TrueSpeed = 127;
    analogWrite(driveport, TrueSpeed);
    driveservo.write(leftangle);
    delay(5000);
    driveservo.write(center);
    }

    void Right() {
    TrueSpeed = 220;
    analogWrite(driveport, TrueSpeed);
    driveservo.write(rightangle);
    delay(5000);
    driveservo.write(center);
    }

    void backRight() {
    TrueSpeed = 127;
    analogWrite(driveport, TrueSpeed);
    driveservo.write(rightangle);
    delay(5000);
    driveservo.write(center);
    }
    
void loop() {
  digitalWrite(t1Pin, LOW);
  delayMicroseconds(5);
  digitalWrite(t1Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(t1Pin, LOW);
  duration1 = pulseIn(e1Pin, HIGH); 
  cm1 = duration1/2/29.1;   
  Serial.println(cm1);  
  delay(500);  

   digitalWrite(t2Pin, LOW);
  delayMicroseconds(5);
  digitalWrite(t2Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(t2Pin, LOW);
  duration = pulseIn(e2Pin, HIGH); 
  cm2 = duration2/2/29.1;   
  Serial.println(cm2);  
  delay(500);   

  Backward();
  if (cm2 > 40){
     backLeft();
     if (cm2 > 40){
      Left();
     }
     if (cm1 > 40){
      Backward();
      if (cm2 > 40){
        Stop();
      }
     }
  }


  

  

}
