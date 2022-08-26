/*
Voice Box Demo Sketch
Written by Ryan Owens
SparkFun Electronics
Modified by Erin Teevens
Divine Child High School Technology and Robotics Club

Uses the Voice Box Shield from SparkFun to send the message to the SpeakJet chip on the shield. 

*/

//Soft serial library used to send serial commands on pin 2 instead of regular serial pin.
#include <SoftwareSerial.h>

//Define the Pin Numbers for the sketch. If you want more messages, you'll need more E pins. 
#define E7  2

#define RDY  2
#define RES  2
#define SPK  2

#define txPin  2

//Create a SoftSerial Objet
SoftwareSerial speakjet = SoftwareSerial(0, txPin);

//The message array contains the command for sounds to be sent in order to inunciate the message. Check the SpeakJet Manual for more information.
//on producing words
//                      No                           weaponizing                                       the                                           robot
char message[] = {21, 90, 142, 164, 21, 127, 5, 147, 131, 199, 135, 141, 157, 8, 167, 129, 143, 5, 21, 114, 8, 169, 8, 128, 5, 21, 127, 148, 7, 137, 7, 164, 8, 171, 8, 135, 8, 193, 7, 188};


void setup()  {
  MessageSetup ();
}

void loop()
{  
  //Send message to the SpeakJet module
  MessagePlay();
  while(1);
}

void MessageSetup () {
 {
  //Configure the pins for the SpeakJet module
  pinMode(txPin, OUTPUT);
  pinMode(SPK, INPUT);
 
  //Set up a serial port to talk from Arduino to the SpeakJet module on pin 3.
  speakjet.begin(9600);    
  
  //Configure the Ready pin as an input
  pinMode(RDY, INPUT);
  
  //Configure Reset line as an output
  pinMode(RES, OUTPUT);
       
  //Configure all of the Event pins as outputs from Arduino, and set them Low.
  for(int i=E7; i<=E7; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  
  //All I/O pins are configured. Reset the SpeakJet module
  digitalWrite(RES, LOW);
  delay(100);
  digitalWrite(RES, HIGH);
  
} 
}

void MessagePlay () { 
  speakjet.print(message);
  while (1);
}
