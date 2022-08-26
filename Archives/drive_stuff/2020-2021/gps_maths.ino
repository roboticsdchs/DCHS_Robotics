
#include <TinyGPS++.h> // Include the TinyGPS++ library
TinyGPSPlus tinyGPS; // Create a TinyGPSPlus object

#define GPS_BAUD 9600 // GPS module baud rate. GP3906 defaults to 9600.

// If you're using an Arduino Uno, RedBoard, or any board that uses the
// 0/1 UART for programming/Serial monitor-ing, use SoftwareSerial:
#include <SoftwareSerial.h>
#define ARDUINO_GPS_RX 9 // GPS TX, Arduino RX pin
#define ARDUINO_GPS_TX 8 // GPS RX, Arduino TX pin
SoftwareSerial ssGPS(ARDUINO_GPS_TX, ARDUINO_GPS_RX); // Create a SoftwareSerial

// Set gpsPort to either ssGPS if using SoftwareSerial or Serial1 if using an
// Arduino with a dedicated hardware serial port
#define gpsPort ssGPS  // Alternatively, use Serial1 on the Leonardo

// Define the serial monitor port. On the Uno, and Leonardo this is 'Serial'
//  on other boards this may be 'SerialUSB'
#define SerialMonitor; Serial

#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

TinyGPSPlus gps;


void setup(){
  SerialMonitor.begin(9600);
  gpsPort.begin(GPS_BAUD);
  /* Initialise the sensor */
  if (!mag.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1)
      ;
  }
}
int to_distance = 100;

int to_course = 0;

int heading = 355;

void loop()
{
  double zeroed = heading - to_course 
  SerialMonitor.print("Movement Instructions\n");
  if(to_distance == 0){
    SerialMonitor.print("Stop\n");
  }
  else if(zeroed == 0){
    SerialMonitor.print("Forward\n");
  }
  // not working NEED to RESTET WHEN GET TO 360/0 
  else if(zeroed > 180){
    if(zeroed > 40){
      SerialMonitor.print("turn to right: 40\n");
    }
    else{
      SerialMonitor.print("turn to right:");
      SerialMonitor.print(zeroed *-1);
      SerialMonitor.print("\n");
    }
  }
  else if(zeroed <= 180){
    if(zeroed < -40){
      SerialMonitor.print("turn to left: -40");
    }
    else{
      SerialMonitor.print("turn to left:");
      SerialMonitor.print(zeroed * -1);
      SerialMonitor.print("\n");
    }
  }
}
