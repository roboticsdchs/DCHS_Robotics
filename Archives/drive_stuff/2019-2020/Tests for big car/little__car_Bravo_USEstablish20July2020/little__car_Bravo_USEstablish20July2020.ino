#include <Servo.h>

Servo myservo;
int PWMA = 6;
int DIRA = 10;


// defines arduino pins numbers
const int echoPin0 = 8;
const int trigPin0 = 11;
const int echoPin1 = 2;
const int trigPin1 = 3;
const int echoPin2 = 6;
const int trigPin2 = 7;
//int pin = 8;
/*const int trigPin3 = 9;
const int echoPin3 = 10;*/
// defines variables
long duration0;
int distance0;
long duration1;
int distance1;

long duration2;
int distance2;
/*long duration3;
int distance3;*/


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
digitalWrite(trigPin0, LOW);
delayMicroseconds(2);
digitalWrite(trigPin0, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin0, LOW);
duration0 = pulseIn(echoPin0, HIGH);
distance0= duration0*0.034/2;
Serial.print("Sensor 1: ");
Serial.println(distance0);

digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1= duration1*0.034/2;
Serial.print("Sensor 2: ");
Serial.println(distance1);
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);

digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2= duration2*0.034/2;
Serial.print("Sensor 3: ");
Serial.println(distance2);
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);

//digitalWrite(trigPin3, HIGH);
//delayMicroseconds(10);
//digitalWrite(trigPin3, LOW);
//duration3 = pulseIn(echoPin3, HIGH);
//distance3= duration3*0.034/2;
//Serial.print("Sensor 4: ");
//Serial.println(distance3);
delay(10);

}



void loop() {
  sensor();
  

}

void setup() 
{
  
pinMode (DIRA, OUTPUT);
pinMode (PWMA, OUTPUT);
pinMode(trigPin0, OUTPUT); // Sets the trigPin as an Output
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
/*pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output*/
//pinMode(pin, OUTPUT);
pinMode(echoPin0, INPUT); // Sets the echoPin as an Input
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
/*pinMode(echoPin2, INPUT); // Sets the echoPin as an 
pinMode(echoPin3, INPUT); // Sets the echoPin as an Input*/
Serial.begin(9600); // Starts the serial communication
//myservo.attach(6);

/*for(int i = 0; i < 1000; i++){
  forward();
  delay(10);
  sensor();
}
motorstop();*/


}
