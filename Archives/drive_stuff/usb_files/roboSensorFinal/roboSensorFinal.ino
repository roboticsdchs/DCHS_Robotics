//This code was created on behalf of the DCHS Robotics Team.  Deletion of this file will incur the wrath of ten immensely pissed-off nerds.  You have been warned.

//For my teammates and future roboticists, this code is for an Arduino program to run multiple ultrasonic transmitters at once. 
//These implements operate similarly to how bats and aquatic mammals use echolocation to find their prey, by emmiting a pulse that cannot be heard by human ears
//towards wherever the sensor is pointed, then determining the distance of the nearest object based on how long it takes for the sound to echo back to the receiver.
//You know how you can measure how far away a storm is by counting between a lightning strike and the thunderclap?  This works on the same principle.
//The essential implements of the device's contruction were two HC-SR04 ultrasonic transmitters (the ones I used were made by SparkFun), and an Arduino Duemilanove board.

#define triggerR 4 //The right trigger, performs vibrations necessary to create echo 
#define infoR 3  //The right Echo pin, listens and times the length between when the sound was emitted and when the sound echoes back.
#define triggerL 12 //The left trigger, works more or less the same.
#define infoL 8      //The left Echo, works the same as the infoR pin.


void setup() {
Serial.begin(9600);
pinMode(triggerL,OUTPUT);
pinMode(infoL,INPUT);
pinMode(triggerR,OUTPUT);
pinMode(infoR,INPUT);
       //Sets up the Serial Monitor to find data.
}

void loop() {
  //prototype code for front two sensors:
long leftVal,leftRead, rightVal,rightRead;   
//leftVal = left Value, this variable stores the length of the echo.  The data's pretty inscrutable on its own, but it can be converted into something more useful.
//leftRead = left Reading, this variable converts the previous variable's value in centimeters.  Good for calibrating.
//The "right" variables work more or less the same. 
//front right sensor:
digitalWrite(triggerL,LOW);
delayMicroseconds(2);
digitalWrite(triggerL,HIGH);
delayMicroseconds(10);
digitalWrite(triggerL,LOW);
leftVal = pulseIn(infoL,HIGH);
leftRead = (leftVal / 2) / 29.1;
Serial.print("L:  ");
Serial.println(leftRead);

delayMicroseconds(50);

digitalWrite(triggerR,LOW);
delayMicroseconds(2);
digitalWrite(triggerR,HIGH);
delayMicroseconds(10);
digitalWrite(triggerR,LOW);
rightVal = pulseIn(infoR,HIGH);
rightRead = (rightVal / 2) / 29.1;

Serial.print("R:   ");
Serial.println(rightRead);
//tells the sonar module on the right to emit an ultrasonic pulse.  

//front left sensor:

//Formats the Serial Monitor's data into something legible.
}

