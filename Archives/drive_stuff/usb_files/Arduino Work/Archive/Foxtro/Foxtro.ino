
const int ledPin =  13;      // the number of the LED pin

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(55555);

int heading = 90; //heading provides reference point for servo movement
const int interruptPin = 2;     // the number of the interrupt pin
long changes = 0;

//float desiredHeading;
//float tempheading;
//float cHeading;

void setup() {
  Wire.begin(1); // join i2c bus (address optional for master)
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  pinMode(10, OUTPUT);                   //establishes 10 as servo pin

  Serial.println("ready");
  delay(500);                           //buffer
  pinMode(11, OUTPUT);                  //pin 11 controls motor controller. make sure pin 11 is connected to the motor controller.
  pinMode(interruptPin, INPUT);
  attachInterrupt(0, pin_ISR, CHANGE); // Attach an interrupt to the ISR vector
//  analogWrite(11, 210);                //210 = speed of car. aka very slow
  //  delay(3000);
}

byte x = 0;

void loop() {
  uint16_t blocks;
  char buf[32];
  int pwm = (heading * 11) + 500;    // Makes PWM a Global Variable. See below for PWM definition
  //  Wire.beginTransmission(8); // transmit to device #8
  //  Wire.write("x is ");        // sends five bytes
  //  Wire.write(x);              // sends one byte
  //  Wire.endTransmission();    // stop transmitting
  //
  //  x++;
  //  delay(500);
  servoPulse(90);
  delay(100);
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) {   // loop through all but the last
    if (Wire.read() == 3)
    {
      //turn left
      analogWrite(11,210);
      servoPulse(45);
      delay(2000);
      servoPulse(90);
      analogWrite(11,0);
//      difference = tempheading + 90;
//      //      servoPulse(135);
//      if (tempheading == difference - 5 || tempheading == difference + 5)
//      {
//        servoPulse(90);
//        //   delay(2000);
//        //        analogWrite(11, 0);
////      }
//      while (tempheading != difference - 5 || tempheading != difference + 5) {
//        servoPulse(135);
//        analogWrite(11,210);
////        headingCalc();
//      }
    }
    if (Wire.read() == 4)
    {
      //Go Straight
      servoPulse(90);
      analogWrite(11, 210);
      delay(2000);
      analogWrite(11, 0);
    }
    if (Wire.read() == 5)
    {
      //   turn right
      analogWrite(11, 210);
      servoPulse(135);
      delay(2000);
      analogWrite(11, 0);
//      difference = tempheading - 90;
//      // servoPulse(45);
//      if (tempheading == difference - 5 || tempheading == difference + 5)
//      {
//        servoPulse(90);
//        delay(2000);
//        //        analogWrite(11, 0);
//      }
//      while (tempheading != difference - 5 || tempheading != difference + 5) {
//        servoPulse(45);
//        headingCalc();
//      }
    }
  }
}

void servoPulse (int angle) // controls servo
{
  int pwm = (angle * 11) + 500;    // Convert angle to microseconds
  digitalWrite(10, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(10, LOW);
  delay(50);                   // Refresh cycle of servo
}


void pin_ISR() {
  changes++;                    //counts up everytime wheel rotates
}

//
//void headingCalc() {
//  sensors_event_t event;
//  mag.getEvent(&event);
//
//  float Pi = 3.14159;
//
//  // Calculate the angle of the vector y,x
//  tempheading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
//}

