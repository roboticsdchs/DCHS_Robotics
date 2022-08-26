#include <XBOXRECV.h>
#include<Servo.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
USB Usb;
XBOXRECV Xbox(&Usb);

/* Define the rotational speed of the motor. MUST be between 0 and 255. */
int Motorpin = 6;
int Turnpin = 5;
int Stick = 0;
int Speed=1;
int Turn=1;
int ActualSpeed = 90;
int ActualTurn = 81;
int NoTurn = 1;
int i;

Servo Move;
Servo Turning;
void setup() {
  Move.attach(Motorpin);
  Turning.attach(Turnpin);
  TCCR1B = TCCR1B & 0b11111000 | 0x02;
  Serial.begin(9600);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  pinMode (Motorpin, OUTPUT);
  pinMode (Turnpin, OUTPUT);
  
}

void loop() {
  NoTurn = 1;
  Usb.Task(); 
  Speed = map((Xbox.getButtonPress(R2, 0)-Xbox.getButtonPress(L2,0)), -255, 255, 0, 180);
  Stick = Xbox.getAnalogHat(LeftHatX, 0);
  if(i%20==0){
    if(Stick<-7500){
    Turn = map(Stick,-7501, -32767, 86, 78);
    NoTurn = 0;
  }
  if(Stick>7500){
    Turn = map(Stick,7501, 32767, 86, 95);
    NoTurn = 0;
  }
  if(NoTurn>0){
    Turn = 86;
  }
  if (Speed > 85){
    //Speed = map(Xbox.getButtonPress(R2, 0), 0, 255, 90, 180);
  }
  if(ActualSpeed>Speed){
    ActualSpeed = ActualSpeed - 3;
  }
  else if(ActualSpeed<Speed){
    ActualSpeed = ActualSpeed +3;
  }
  if((ActualSpeed<92&&ActualSpeed>88)||(Xbox.getButtonPress(R2, 0)<3&&Xbox.getButtonPress(L2, 0)<3)){
    ActualSpeed = 90;
  }
  Serial.print("Turn = ");
  Serial.print(Turn);
  Serial.print(" Speed = ");
  Serial.println(ActualSpeed);
  Move.write(ActualSpeed);
  Turning.write(Turn);
  }
  i++;
}
