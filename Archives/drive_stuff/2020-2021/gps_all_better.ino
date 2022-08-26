/******************************************************************************
  TinyGPSPlus_GPS_Shield.ino
  TinyGPS++ Library Example for the SparkFun GPS Logger Shield
  By Jim Lindblom @ SparkFun Electronics
  February 9, 2016
  https://github.com/sparkfun/GPS_Shield

  This example uses SoftwareSerial to communicate with the GPS module on
  pins 8 and 9. It uses the TinyGPS++ library to parse the NMEA strings sent
  by the GPS module, and prints interesting GPS information to the serial
  monitor.

  After uploading the code, open your serial monitor, set it to 9600 baud, and
  watch for latitude, longitude, altitude, course, speed, date, time, and the
  number of visible satellites.

  Resources:
  TinyGPS++ Library  - https://github.com/mikalhart/TinyGPSPlus/releases
  SoftwareSerial Library

  Development/hardware environment specifics:
  Arduino IDE 1.6.7
  GPS Logger Shield v2.0 - Make sure the UART switch is set to SW-UART
  Arduino Uno, RedBoard, Pro, etc.
******************************************************************************/


//NEED TO follow https://learn.sparkfun.com/tutorials/gps-logger-shield-hookup-guide#software-serial-and-spi-on-other-microcontrollers for converting to mega 2560
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

TinyGPSPlus gps;

#include "Wire.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303.h>

Adafruit_LSM303 lsm;

float Mx, My, Mz; // Raw Magnetometer measurements
float Mxc, Myc, Mzc; // Calibrated Magnetometer measurements
float Mxcn, Mycn, Mzcn; // Normalized Magnetometer measurements


float Ax, Ay, Az; // Raw Accelerometer measurments
float Axc, Ayc, Azc;  // Calibrated Accelerometer mesurements
float Axcn, Aycn, Azcn; // Normalized Accelerometer measurements


float norm_a, norm_m;

double pitch, roll;
double pitch_print, roll_print;
double tiltcnf;

double Xh, Yh;  // Tilt compensated values for heading calculation
float headingct; // Calibrated and tilt compensated heading


//calibrated_values[3] is the global array where the calibrated data will be placed
//calibrated_values[3]: [0]=Xc, [1]=Yc, [2]=Zc
float calibrated_mag_values[3];
float calibrated_acc_values[3];

float alpha = 0.25; // Low-Pass Filtercoefficient

// Filtered Magnetometer measurements
float Mxcnf = 0;
float Mycnf = 0;
float Mzcnf = 0;

// Filtered Accelerometer measurements
float Axcnf = 0;
float Aycnf = 0;
float Azcnf = 0;



void setup()
{
  Serial.begin(9600);
  gpsPort.begin(GPS_BAUD);
  Wire.begin();
  lsm.begin();
}

void loop()
{   
  printGPSinfo();
  
  static const double T_LAT =  42.285530, T_LON =  -83.531700;
                               

  unsigned long distance_to = (unsigned long)TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), T_LAT, T_LON) / 1000;
  
  Serial.print("distance_to:");
  Serial.print(distance_to);
  Serial.print("\n");

  double course_to = TinyGPSPlus::courseTo(gps.location.lat(), gps.location.lng(), T_LAT, T_LON);

  Serial.print("course_to:");
  Serial.print(course_to);
  Serial.print("\n");

//Compass needs to be mounted flat and pointing in the right direction otherwise the readings are all over the place!
  compass();
  
  if (headingct > course_to + 180){
    headingct = headingct - 360;
  }
  if(course_to > headingct + 180){
    course_to = course_to - 360;
  }
  double zeroed = headingct - course_to; 
  //if(gps.location.lat() - 0.0001 < T_LAT < gps.location.lat() + 0.0001 && gps.location.lng() - 0.0001 < T_LON < gps.location.lng() + 0.0001){
  if (distance_to == 0 ){
    Serial.println("Stop\n");
  }
  else{
    Serial.print("turn to:");
    Serial.println(zeroed * -1);
  }

  
  // "Smart delay" looks for GPS data while the Arduino's not doing anything else
  smartDelay(1000); 
  Serial.print("\n-----------------------------------------------------------------------------------------\n");
}

void printGPSinfo(){
  // Print latitude, longitude, altitude in feet, course, speed, date, time,
  // and the number of visible satellites.
  Serial.print("Lat: "); Serial.println(tinyGPS.location.lat(), 6);
  Serial.print("Long: "); Serial.println(tinyGPS.location.lng(), 6);
  Serial.print("Alt: "); Serial.println(tinyGPS.altitude.feet());
  Serial.print("Course: "); Serial.println(tinyGPS.course.deg());
  Serial.print("Speed: "); Serial.println(tinyGPS.speed.mph());
  Serial.print("Date: "); printDate();
  Serial.print("Time: "); printTime();
  Serial.print("Sats: "); Serial.println(tinyGPS.satellites.value());
}


void compass(){
  lsm.read();

  float values_from_magnetometer[3];
  float values_from_accelerometer[3];

  getRawValuesMag();

  values_from_magnetometer[0] = Mx;
  values_from_magnetometer[1] = My;
  values_from_magnetometer[2] = Mz;

  transformation_mag(values_from_magnetometer);

  Mxc = calibrated_mag_values[0];
  Myc = calibrated_mag_values[1];
  Mzc = calibrated_mag_values[2];

  getRawValuesAcc();

  values_from_accelerometer[0] = Ax;
  values_from_accelerometer[1] = Ay;
  values_from_accelerometer[2] = Az;

  transformation_acc(values_from_accelerometer);

  Axc = calibrated_acc_values[0];
  Ayc = calibrated_acc_values[1];
  Azc = calibrated_acc_values[2];

  //  Normalizing
  norm_m = sqrt(sq(Mxc) + sq(Myc) + sq(Mzc)); //original code did not appear to normalize, and this seems to help
  Mxcn = Mxc / norm_m;
  Mycn = Myc / norm_m;
  Mzcn = Mzc / norm_m;

  norm_a = sqrt(sq(Ax) + sq(Ay) + sq(Az)); //original code did not appear to normalize, and this seems to help
  Axcn = Axc / norm_a;
  Aycn = Ayc / norm_a;
  Azcn = Azc / norm_a;


  // Low-Pass filter magnetometer
  Mxcnf = Mxcn * alpha + (Mxcnf * (1.0 - alpha));
  Mycnf = Mycn * alpha + (Mycnf * (1.0 - alpha));
  Mzcnf = Mzcn * alpha + (Mzcnf * (1.0 - alpha));

  // Low-Pass filter accelerometer
  Axcnf = Axcn * alpha + (Axcnf * (1.0 - alpha));
  Aycnf = Aycn * alpha + (Aycnf * (1.0 - alpha));
  Azcnf = Azcn * alpha + (Azcnf * (1.0 - alpha));


  // Calculating pitch and roll angles following Application Note
  pitch = (double) asin((double) - Axcnf);
  pitch_print = pitch * 180 / PI;
  roll = (double) asin((double) Aycnf / cos((double) pitch));
  roll_print = roll * 180 / PI;


  //  Calculating heading with raw measurements not tilt compensated
  float heading = (double)atan2((double)My, (double)Mx) * 180 / PI;
  if (heading < 0) {
    heading = 360 + heading;
  }

  //  Calculating heading with calibrated measurements not tilt compensated
  float headingc = (double)atan2((double)Myc, (double)Mxc) * 180 / PI;
  if (headingc < 0) {
    headingc = 360 + headingc;
  }

  //  Calculating tilt compensated heading
  Xh = Mxcnf * cos((double)pitch) + Mzcnf * sin((double)pitch);
  Yh = Mxcnf * sin((double)roll) * sin((double)pitch) + Mycnf * cos((double)roll) - Mzcnf * sin((double)roll) * cos((double)pitch);
  headingct = (atan2(Yh, Xh)) * 180 / PI;
  if (headingct < 0) {
    headingct = 360 + headingct;
  }


  //Calculating Tilt angle in degrees
  tiltcnf = (double)atan2((double)fabs(Azcnf), (double)Axcnf) * 180 / PI;
  /*
  Serial.flush();

  // Display raw magnetometer values
  Serial.println("Magnetometer raw measurements");
  Serial.print("Mx: "); Serial.print(Mx); Serial.print("; ");
  Serial.print("My: "); Serial.print(My); Serial.print("; ");
  Serial.print("Mz: "); Serial.println(Mz);

  // Display calibrated magnetometer values
  Serial.println("Magnetometer calibrated measurements");
  Serial.print("Mxc: "); Serial.print(Mxc); Serial.print("; ");
  Serial.print("Myc: "); Serial.print(Myc); Serial.print("; ");
  Serial.print("Mzc: "); Serial.println(Mzc);
  Serial.println("--------------------------------------");

  // Display raw accelerometer measurements in milliG
  Serial.println("Accelerometer raw measurements");
  Serial.print("Ax: "); Serial.print(Ax); Serial.print("; ");
  Serial.print("Ay: "); Serial.print(Ay); Serial.print("; ");
  Serial.print("Az: "); Serial.println(Az);

  // Display calibrated accelerometer measurements in milliG
  Serial.println("Accelerometer calibrated measurements");
  Serial.print("Axc: "); Serial.print(Axc); Serial.print("; ");
  Serial.print("Ayc: "); Serial.print(Ayc); Serial.print("; ");
  Serial.print("Azc: "); Serial.println(Azc);
  Serial.println("--------------------------------------");

  // Display Heading in degrees North = 0°--> 360° turning clockwise
  Serial.print ("Heading raw: "); Serial.println (heading);
  Serial.print ("Heading calibrated: "); Serial.println (headingc);
  Serial.print ("Heading tilt compensated: "); Serial.println (headingct);
  Serial.println("--------------------------------------");


  // Display Tilt angle in degrees
  Serial.print("Tilt raw: "); Serial.println((double)atan2((double)fabs(Az), (double)Ax) * 180 / PI);
  Serial.print("Tilt calibrated: "); Serial.println(tiltcnf);

  // Display Pitch and Roll angles in degrees
  Serial.print ("Pitch: "); Serial.println (pitch_print);
  Serial.print ("Roll: "); Serial.println (roll_print);
  Serial.println("--------------------------------------");
  Serial.println();
  Serial.println();
  */
  Serial.print("heading raw: "); Serial.println (heading);
  Serial.print("heading compinsated"); Serial.println (headingct);
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
  Serial.print(tinyGPS.date.day());
  Serial.print("/");
  Serial.print(tinyGPS.date.month());
  Serial.print("/");
  Serial.println(tinyGPS.date.year());
}

// printTime() formats the time into "hh:mm:ss", and prints leading 0's
// where they're called for.
void printTime()
{
  Serial.print(tinyGPS.time.hour());
  Serial.print(":");
  if (tinyGPS.time.minute() < 10) Serial.print('0');
  Serial.print(tinyGPS.time.minute());
  Serial.print(":");
  if (tinyGPS.time.second() < 10) Serial.print('0');
  Serial.println(tinyGPS.time.second());
}


// Read the raw measurements
void getRawValuesMag()
{
  Mx = (float)lsm.magData.x;
  My = (float)lsm.magData.y;
  Mz = (float)lsm.magData.z;
}

void getRawValuesAcc()
{
  Ax = (int)lsm.accelData.x;
  Ay = (int)lsm.accelData.y;
  Az = (int)lsm.accelData.z;
}


//transformation(float uncalibrated_values[3]) is the function of the magnetometer data correction
//uncalibrated_values[3] is the array of the non calibrated magnetometer data
//uncalibrated_values[3]: [0]=Xnc, [1]=Ync, [2]=Znc

void transformation_mag(float uncalibrated_values[3])
{
  //calibration_matrix[3][3] is the transformation matrix
  //replace M11, M12,..,M33 with your transformation matrix data
  double calibration_matrix[3][3] =
  {
    {1.025, 0.026, 0.004},
    {0.003, 1.024, 0.002},
    {0.018, -0.002, 1.251}
  };
  //bias[3] is the bias
  //replace Bx, By, Bz with your bias data
  double bias[3] =
  {
    -6.278,
    -101.76,
    -179.707
  };
  //calculation
  for (int i = 0; i < 3; ++i) uncalibrated_values[i] = uncalibrated_values[i] - bias[i];
  float result[3] = {0, 0, 0};
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      result[i] += calibration_matrix[i][j] * uncalibrated_values[j];
  for (int i = 0; i < 3; ++i) calibrated_mag_values[i] = result[i];
}


//transformation(float uncalibrated_values[3]) is the function of the accelerometer data correction
//uncalibrated_values[3] is the array of the non calibrated magnetometer data
//uncalibrated_values[3]: [0]=Xnc, [1]=Ync, [2]=Znc

void transformation_acc(float uncalibrated_values[3])
{
  //calibration_matrix[3][3] is the transformation matrix
  //replace ACC11(M11), ACC12(M12),..,ACC33(M33) with your transformation matrix data
  double calibration_matrix[3][3] =
  {
    {0.98, 0.002, 0.001},
    { -0.005, 1.003, 0.007},
    {0.011, -0.005, 1.019}
  };
  //zero-g[3] is the zero-g offset
  //replace ACC10(Bx), ACC20(By), ACC30(Bz) with your zero-g offset data
  double zero_g[3] =
  {
    -30.988,
    10.754,
    -8.697
  };
  //calculation
  for (int i = 0; i < 3; ++i) uncalibrated_values[i] = uncalibrated_values[i] - zero_g[i];
  float result[3] = {0, 0, 0};
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      result[i] += calibration_matrix[i][j] * uncalibrated_values[j];
  for (int i = 0; i < 3; ++i) calibrated_acc_values[i] = result[i];
}
