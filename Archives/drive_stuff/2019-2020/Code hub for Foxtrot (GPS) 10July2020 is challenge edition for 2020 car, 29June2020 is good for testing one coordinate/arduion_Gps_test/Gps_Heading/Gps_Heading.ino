/*
 * This sketch demonstrates how to calculate a compass heading from two GPS points.
 * Prints out the 0-360 compass heading from the current location to the target waypoint
 */

// Sample GPS coordinates representing the current location. 
float currentLatitude  =   90.590214;
float currentLongitude =  -121.767142;


void setup() {
  Serial.begin(9600);
}

void loop() {

  Serial.print("North: ");
  Serial.println(getWaypointHeading(38.601164, -121.767199));  // a point due north

  Serial.print("East: ");
  Serial.println(getWaypointHeading(38.590264, -121.761617));  // a point due east

  Serial.print("South: ");
  Serial.println(getWaypointHeading(38.586864, -121.767143));  // a point due south

  Serial.print("West: ");
  Serial.println(getWaypointHeading(38.590215, -121.803073));  // a point due west
 
  while(1);

}

/*
 * This function takes a lat/log and returns the 0-360 compass heading from the current 
 * globally defined lat/log
 */
int getWaypointHeading(float targetLatitude, float targetLongitude) {

  // radians
  float heading = atan2(targetLatitude - currentLatitude, targetLongitude - currentLongitude);

  // convert to degrees 0 to 180/-180
  heading *= (180 / 3.14159);

  // convert to 0-360 compass degrees, North = 0
  heading = (450 - (int)heading) % 360;

  return heading;

}
