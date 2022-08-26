#include <TinyGPS++.h> // Include the TinyGPS++ library
TinyGPSPlus tinyGPS; // Create a TinyGPSPlus object
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>;

int leftangle = 39;//for 45 degree angle
int center = 86;
int rightangle = 46; //for 45 degree angle
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
int slightleftangle = 8;//for 10 degree angle
int slightrightangle = 10;//for 10 degree angle
int latlong = 0;

double TLatitudes[] = {42.302940, 42.303630, 42.302139, 42.302928};//E, N, S, W
double TLoingitudes[] = {-83.430343, -83.431129, -83.431129, -83.431953};

Servo turnmotor;
Servo movemotors;





Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(12345);

#include <Ethernet.h>

#include <math.h>
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
double TLatitude  =  TLatitudes[latlong];
double TLongitude =  TLongitudes[latlong];

double CLatitude;
double CLongitude;
float bearingforcalcs;
float headingforcalcs;
float bearing(float lat, float lon, float lat2, float lon2) { //the bearing is the difference between North, the origin, and the point to get to with the GPS.

  float teta1 = radians(lat);
  float teta2 = radians(lat2);
  float delta1 = radians(lat2 - lat);
  float delta2 = radians(lon2 - lon);

  //==================Bearing Formula Calculation================//

  float y = sin(delta2) * cos(teta2);
  float x = cos(teta1) * sin(teta2) - sin(teta1) * cos(teta2) * cos(delta2);
  float bearing = atan2(y, x);
  bearing = degrees(bearing);// radians to degrees
  bearing = (((int)bearing + 360) % 360 );//we don't recommend changing the bearing to an int, but it was just easiest to use modulo here. we can change to be float or double if needed
bearingforcalcs = bearing;
  Serial.print("Bearing:");
  Serial.println(bearing), 10;

  return bearing;


}


double changebearing(float crse, float brg){
  double diffbearing = brg-crse; 
   if (diffbearing > -60 && diffbearing < 60) {
    return Serial.println(diffbearing);
    }
    else if(diffbearing > 60){
    return Serial.println("60");
    }
      else if (diffbearing < -60){
      return Serial.println("-60"); 
      }
    
  }
  double changeheading(float hdg, float brg){
  double diffheading = brg-hdg;
    if(diffheading > -60 && diffheading < 60) {
     return Serial.println(diffheading);   
     if(diffbearing>0){
      slightleft();
      }else {
        slightright();
        }
     }
      else if(diffheading > 60){
      return Serial.println("60"); 
      Left();   
      }
        else if(diffheading < -60) {
        return Serial.println("60"); 
       Right();
        }
  }
  double moving(float Clat, float Clong, float Tlat, float Tlong){
    if((Clat >= Tlat-0.00002&&Clat<=Tlat+0.00002)&&(Clong >= Tlong-0.00002&&Clong<=Tlong+0.00002)){
      
      return Serial.println("motorstop");
      if(latlong == 3){
        Stop();
        }else {
          }
     delay(5000);
     latlong++;
      
      }else{
        Forward();
        return Serial.println("moveforward");
        }
    }
void setup()
{
  turnmotor.attach(turnport);
 movemotors.attach(moveport);
turnmotor.write(center);
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

  // print position, altitude, speed, time/date, and satellites:
  printGPSInfo();

  // "Smart delay" looks for GPS data while the Arduino's not doing anything else
  smartDelay(1000);

}

void printGPSInfo()
{
  // Print latitude, longitude, altitude in feet, course, speed, date, time,
  // and the number of visible satellites.
  SerialMonitor.print("Lat: "); SerialMonitor.println(tinyGPS.location.lat(), 6);
  SerialMonitor.print("Long: "); SerialMonitor.println(tinyGPS.location.lng(), 6);
  CLatitude = tinyGPS.location.lat(), 6;
  CLongitude = tinyGPS.location.lng(), 6;
  SerialMonitor.print("Alt: "); SerialMonitor.println(tinyGPS.altitude.feet());
  SerialMonitor.print("Course: "); SerialMonitor.println(tinyGPS.course.deg());

  SerialMonitor.print("Speed: "); SerialMonitor.println(tinyGPS.speed.mph());
  SerialMonitor.print("Date: "); printDate();
  SerialMonitor.print("Time: "); printTime();
  SerialMonitor.print("Sats: "); SerialMonitor.println(tinyGPS.satellites.value());
  bearing(CLatitude, CLongitude, TLatitude, TLongitude);
  SerialMonitor.print("Heading:"); heading();
  int compasscourse = tinyGPS.course.deg();
  SerialMonitor.print("Movement:"); moving(CLatitude, CLongitude, TLatitude, TLongitude);
  SerialMonitor.print("Change Bearing by:"); changebearing(compasscourse, bearingforcalcs);
  SerialMonitor.print("Change Heading by:"); changeheading(headingforcalcs, bearingforcalcs);
  SerialMonitor.println();

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


double heading() {
  sensors_event_t event;
  mag.getEvent(&event);

  float Pi = 3.14159;

  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y, event.magnetic.x) * 180) / Pi;

  if (heading < 0) {

    heading += 360;
  }
headingforcalcs = heading;
  Serial.println(heading);
}
void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(5000);
}
void Backward() {
  TrueSpeed = 127;
  movemotors.write(70);
  delay(5000);
}
  void Stop() {
    TrueSpeed = 191;
    movemotors.write(90);
    delay(5000);
  }
  void Left() {
    TrueSpeed = 254;
    movemotors.write(110);
    turnmotor.write(leftangle);
    delay(5000);
    turnmotor.write(center);
    }

    void Right() {
    TrueSpeed = 254;
    movemotors.write(110);
    turnmotor.write(rightangle);
    delay(5000);
    turnmotor.write(center);
    }
    void slightright(){
       TrueSpeed = 254;
    movemotors.write(110);
    turnmotor.write(slightrightangle);
    delay(5000);
    turnmotor.write(center);
      }
      void slightleft(){
       TrueSpeed = 254;
    movemotors.write(110);
    turnmotor.write(slightleftangle);
    delay(5000);
    turnmotor.write(center);
      }
