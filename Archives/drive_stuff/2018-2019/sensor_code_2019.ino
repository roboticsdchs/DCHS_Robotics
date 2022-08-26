//DCHS Robotics Club meeting. 2-15-2019.  This code was written for the HC-SR04 Ultrasonic Sensor.  The principle behind it is similar to that of echolocation:
//The T-Pin, or trigger pin, emits a sound with a frequency imperceptible by human ears, which then bounces off the nearest object.  Then the E-Pin, or echo pin, receives the soundwaves 
//reflected back.  The computer determines how far away the closest object is by measuring the time between when the noise is released and when the echo is received. I store that value in a
//variable called duration, which is then converted into centimeters for the sake of convenience.  The Arduino then prints the distance between the sensor and the nearest surface to the 
//serial monitor.  It then delays by about half a second for legibility's sake.

int tPin = 11;  //designates pin 11 on the Arduino board to be the trigger pin. 
int ePin = 9;   //designates pin 9 on the Arduino board to be the echo pin.
long duration, cm;  //establishes the variables "duration" and "cm".  Duration is the variable which stores the length of time it takes for the reflected sound waves to return to the sensor.
//cm is the value of duration converted to centimeters.

void setup() {
   Serial.begin(9600);  //sets up the serial monitor.
   pinMode(tPin, OUTPUT);
   pinMode(ePin, INPUT);
}

void loop() {
  digitalWrite(tPin, LOW);
  delayMicroseconds(5);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW); //the last five lines of code make the module transmit an ultrasonic pulse.
  duration = pulseIn(ePin, HIGH);  //checks how long it took for the ultrasonic waves to echo back to the receiver.
  cm = duration/2/29.1;   //Converts the value stored in "duration" to centimeters, which will make testing more convenient.
  Serial.println(cm);  //Prints the distance measured to the serial monitor.
  delay(500);  //this just makes the serial print more legible.
}
//I used this code to test whether the sensor modules I made for last year's autonomous vehicle competition were still functioning. As it turned out, only one of them worked.  Will have to 
//build another module to test how multiple sensors would function.
//The Arduino to which the module is connected serves two "brain" functions:
//Telling how much time passes between transmission and reception.
//Calculating that value in centimeters.
//One of the limitations of this sensor is that it can only see objects which are directly in front of it.
