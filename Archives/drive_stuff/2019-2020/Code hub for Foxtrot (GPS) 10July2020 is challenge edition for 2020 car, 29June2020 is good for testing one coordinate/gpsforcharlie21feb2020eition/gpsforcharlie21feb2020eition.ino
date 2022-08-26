


#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

#include <Ethernet.h>

#include <math.h>

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
#define SerialMonitor Serial



double TLatitude  =  25.77481;
double TLongitude =  -80.19773;

 
double CLatitude  = 42.3314; //tinyGPS.location.lat(), 50;
double CLongitude = -83.0458; //tinyGPS.location.lng(), 50;
float heading1;
int degree1;
int degree2;
float bearing(float lat,float lon,float lat2,float lon2){

   float teta1 = radians(lat);
    float teta2 = radians(lat2);
    float delta1 = radians(lat2-lat);
    float delta2 = radians(lon2-lon);

    //==================Heading Formula Calculation================//

    float y = sin(delta2) * cos(teta2);
    float x = cos(teta1)*sin(teta2) - sin(teta1)*cos(teta2)*cos(delta2);
    float brng = atan2(y,x);
    brng = degrees(brng);// radians to degrees
    brng = ( ((int)brng + 360) % 360 ); 

    Serial.print("Heading GPS: ");
    Serial.println(brng), 10;

    return brng;


}


int brg = bearing(CLatitude, CLongitude, TLatitude, TLongitude);
int hd = tinyGPS.course.deg();
int comp = compass();

double moving(float Clat, float Clong, float Tlat, float Tlong){
  if (Clat == Tlat && Clong ==  Tlong) {
    return Serial.println("motorstop");
  }
  else {
    return Serial.println("moveforward");
  }
  }

double turnheading(float heading1, float  bearing){
  int degree1 = bearing - heading1; 
   if (degree1 > -60 && degree1 > 60) {
   return Serial.println(degree1); 
   }
    else if(degree1 > 60){
    return Serial.println("60");
    }
      else if (degree1 < -60){
      return Serial.println("-60"); 
      }
    
  }
double turncompass(float compass1, float bearing2){
  int degree2 = bearing2 - compass1;
    if(degree2 > -60 && degree2 > 60) {
     return Serial.println(degree2);   
     }
      else if(degree2 > 60){
      return Serial.println("turn 60");    
      }
        else if(degree2 < -60) {
        return Serial.println("turn -60"); 
        }
  }
 
void setup(){

  SerialMonitor.begin(9600);
  gpsPort.begin(GPS_BAUD);
  if (!mag.begin()) {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1);
  }

}

void loop()
{
 SerialMonitor.print("Lat: "); SerialMonitor.println(tinyGPS.location.lat(), 50);
  SerialMonitor.print("Long: "); SerialMonitor.println(tinyGPS.location.lng(), 50);
  SerialMonitor.print("Alt: "); SerialMonitor.println(tinyGPS.altitude.feet());
  SerialMonitor.print("Course: "); SerialMonitor.println(tinyGPS.course.deg());
  SerialMonitor.print("Speed: "); SerialMonitor.println(tinyGPS.speed.mph());
  SerialMonitor.print("Date: "); printDate();
  SerialMonitor.print("Time: "); printTime();
  SerialMonitor.print("Sats: "); SerialMonitor.println(tinyGPS.satellites.value());
  //SerialMonitor.print("bearing:");
  bearing(CLatitude, CLongitude, TLatitude, TLongitude); 
  SerialMonitor.print("compass:");compass();
  SerialMonitor.print("moving:");moving(CLatitude, CLongitude, TLatitude, TLongitude);
  SerialMonitor.print("turncompass:");turncompass(hd, brg);
  SerialMonitor.print("turnheading:");turnheading(comp, brg);
  delay(1000);
  //SerialMonitor.print("turnto:"); getto(bearing, heading1); 
  
}



// This custom version of delay() ensures that the tinyGPS object
// is being "fed". From the TinyGPS++ examples.
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    // If data has come in from the GPS module
    while (gpsPort.available())
      tinyGPS.encode(gpsPort.read()); // Send it to the encode function
    // tinyGPS.encode(char) continues to "load" the tinGPS object with new
    // data coming in from the GPS module. As full NMEA strings begin to come in
    // the tinyGPS library will be able to start parsing them for pertinent info
  } while (millis() - start < ms);
}

// printDate() formats the date into dd/mm/yy.
void printDate()
{
  SerialMonitor.print(tinyGPS.date.day());
  SerialMonitor.print("/");
  SerialMonitor.print(tinyGPS.date.month());
  SerialMonitor.print("/");
  SerialMonitor.println(tinyGPS.date.year());
}

// printTime() formats the time into "hh:mm:ss", and prints leading 0's
// where they're called for.
void printTime()
{
  SerialMonitor.print(tinyGPS.time.hour());
  SerialMonitor.print(":");
  if (tinyGPS.time.minute() < 10) SerialMonitor.print('0');
  SerialMonitor.print(tinyGPS.time.minute());
  SerialMonitor.print(":");
  if (tinyGPS.time.second() < 10) SerialMonitor.print('0');
  SerialMonitor.println(tinyGPS.time.second());
}
double compass(){
   /* Get a new sensor event */
  sensors_event_t event;
  mag.getEvent(&event);

  float Pi = 3.14159;

  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;

// Normalize to 0-360
  if (heading < 0) {
    heading = 360 + heading;
  }
  heading1 = heading;
  Serial.println(heading);
  return heading;
  
    }
