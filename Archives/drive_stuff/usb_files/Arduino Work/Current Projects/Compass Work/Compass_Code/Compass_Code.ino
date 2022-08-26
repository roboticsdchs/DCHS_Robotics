#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(55555);

float desiredHeading;
float heading;
float cHeading;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");

  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

  headingCalc();
  desiredHeading = heading;
  Serial.print("desiredHeading: ");
  Serial.println(desiredHeading);
}

void loop() 
{
  /* Get a new sensor event */ 
  headingCalc();
   cHeading = heading;
  Serial.print("Compass Heading: ");
  Serial.println(cHeading);
  float difference = desiredHeading - cHeading;
  Serial.print("Difference: ");
  Serial.println(difference);
  Serial.println("---");
  delay(400);
}

bool headingCalc() {
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

