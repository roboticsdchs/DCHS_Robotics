#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

int  dir;
int heading;
int angle;

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");
  heading = ReadCompass;
  dir = heading;
  angle = 90;
  servoPulse(angle);
  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1);
  }
}

void loop(void)
{
//
// float Pi = 3.14159;
// 
//  sensors_event_t event;
//  mag.getEvent(&event);
//  // Calculate the angle of the vector y,x
//  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;
  ReadCompass();
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading; //Take this out to disable 0 to 360 wrap. Replaced with 180, -180 wrap.
  }

  Serial.print("Compass heading: ");
  Serial.println(heading);
  delay(500);
  
  if (heading < dir)
  {
    angle++;
    servoPulse(angle);
  }
  if (heading > dir)
  {
    angle--;
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
  digitalWrite(2, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(2, LOW);
  delay(50);                   // Refresh cycle of servo
}
