#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
 
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
 
void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");

  /* Initialise the sensor */
if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}
 
void loop(void) 
{
/* Get a new sensor event */ 
sensors_event_t event; 
mag.getEvent(&event);

  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  
  // Normalize to 0-360
if (heading < 0) {

    heading = 360 + heading;

}
if (heading >= 0 && heading < 90) {
  Serial.println("N");
}

else if (heading >= 90 && heading < 180) {
  Serial.println("E");
  }

else if (heading >= 180 && heading < 270) {
  Serial.println("S");
  }

else if (heading >= 270 && heading < 360) {
  Serial.println("W");
 
  }

delay (250);
}
