#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_STRIP_PIN    6
#define LED_WHEEL_PIN    7
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 100
Adafruit_NeoPixel strip(LED_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wheel = Adafruit_NeoPixel(12, LED_WHEEL_PIN, NEO_GRB + NEO_KHZ800);
#include <TinyGPS++.h> // Include the TinyGPS++ library
TinyGPSPlus tinyGPS; // Create a TinyGPSPlus object
#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>;

int leftangle = 112;//for 45 degree angle minus 8
int center = 120;
int rightangle = 139; //for 45 degree angle plus 7
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
int slightleftangle = 116; //minus 4
int slightrightangle = 130; //plus 4
int endlight = 13;




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

// Set gpsPort to either ssGPS if using SoftwareSerial or Serial if using an
// Arduino with a dedicated hardware serial port
#define gpsPort ssGPS  // Alternatively, use Serial1 on the Leonardo

// Define the serial monitor port. On the Uno, and Leonardo this is 'Serial'
//  on other boards this may be 'SerialUSB'
#define SerialMonitor Serial
double TLatitude =  42.302928;
double TLongitude  =  -83.430252;
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


double changebearing(float crse, float brg) {
  double diffbearing = brg - crse;
  if (diffbearing > -60 && diffbearing < 60) {
    return Serial.println(diffbearing);
  }
  else if (diffbearing >= 60) {
    return Serial.println("60");
  }
  else if (diffbearing <= -60) {
    return Serial.println("-60");
  }

}
double changeheading(float hdg, float brg) {
  double diffheading = brg - hdg;
  if (diffheading > -30 && diffheading < 30) {
     turnmotor.write(center);
     Forward();
    return Serial.println(diffheading);  
  } else if (diffheading >= 30 && diffheading < 90) {
    slightRight();
  } else if (diffheading <= -30 && diffheading > -90) {
    slightLeft();
  } else if (diffheading >= 90 && diffheading <= 180) {
    Right();
    return Serial.println("60");
    
  } else if (diffheading <= -90 && diffheading >= -180) {
    Left();
    return Serial.println("-60");
  }else if (diffheading < -180) {
    Left();
    return Serial.println("-60");
  }else if (diffheading > 180) {
    Right();
    return Serial.println("-60");
  }
}
double moving(float Clat, float Clong, float Tlat, float Tlong) {
  if (Clat<= Tlat+.00008&& Clat>= Tlat-.00008&& Clong<= Tlong+.00008&& Clong>= Tlong-.00008) {
    digitalWrite(endlight, HIGH);
    colorWipeStrip(strip.Color(  0,   0, 255), 50); // Blue
    colorWipeWheel(wheel.Color(  0,   0, 255), 50); // Blue 
    delay(700);
    Stop();
    return Serial.println("motorstop");
  } else {
    Forward();
    return Serial.println("moveforward");
  }
}
void setup() {
  pinMode(endlight,OUTPUT);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  wheel.begin();
  wheel.setBrightness(50);
  wheel.show(); // Initialize all pixels to 'off'
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
  delay(10000);
  SerialMonitor.begin(9600);
  gpsPort.begin(GPS_BAUD);
   colorWipeStrip(strip.Color(  255,   0, 0), 50); // Red
   colorWipeWheel(wheel.Color(  255,   0, 0), 50); // Red
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
  turnmotor.write(leftangle);
  delay(5000);
  turnmotor.write(center);
}

void Right() {
  TrueSpeed = 254;
  turnmotor.write(rightangle);
  delay(5000);
  turnmotor.write(center);
}
void slightRight() {
  TrueSpeed = 254;
  turnmotor.write(slightrightangle);
  delay(5000);
  turnmotor.write(center);
}

void slightLeft() {
  //TrueSpeed = 254;
  turnmotor.write(slightleftangle);
  delay(5000);
  turnmotor.write(center);
}
void colorWipeStrip(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void colorWipeWheel(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    wheel.setPixelColor(i, c);
   wheel.show();
    delay(wait);
  }
}
