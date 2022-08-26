#include <Servo.h>

Servo myservo;
int PWMA = 3;
int DIRA = 12;


// defines arduino pins numbers
const int trigPin = 9;
const int echoPin = 4;
int pin=8;
// defines variables
long duration;
int distance;


void forward(){
  myservo.write(90);
  digitalWrite(PWMA, HIGH);
  digitalWrite(DIRA, HIGH);
}
void right(){
  digitalWrite(PWMA, HIGH);
  myservo.write(50);
  digitalWrite(DIRA, HIGH);
}
void left(){
  digitalWrite(PWMA, HIGH);
  myservo.write(130);
  digitalWrite(DIRA, HIGH);
}


void motorstop(){
  digitalWrite(PWMA, LOW); 
  digitalWrite(DIRA, LOW);
  }

void sensor(){
  digitalWrite(pin,HIGH);
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
Serial.println(distance);
delay(10);

}



void loop() {
  sensor();
  
if(distance<300){
  motorstop();
  }
  else{
    forward();
    }
}

void setup() 
{
pinMode (DIRA, OUTPUT);
pinMode (PWMA, OUTPUT);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(pin, OUTPUT);
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
myservo.attach(6);

/*for(int i = 0; i < 1000; i++){
  forward();
  delay(10);
  sensor();
}
motorstop();*/


}
