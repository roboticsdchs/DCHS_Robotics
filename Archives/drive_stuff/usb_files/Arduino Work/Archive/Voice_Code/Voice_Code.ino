/*
Voice Box Sketch
Written by Ryan Owens
SparkFun Electronics
Modified by Erin Teevens

Use a Voicebox Shield to say "Robots." Input is cut out, 
this code only uses the output.If you want to send multiple messages, 
you'll need more E pins, going up numbers
*/

//Soft serial library used to send serial commands on pin 2 instead of 
//regular serial pin.
#include <SoftwareSerial.h>

//Define the Pin Numbers for the sketch.
#define E7  A0

#define RDY  A1
#define RES  A2
#define SPK  A3

#define txPin  2

//Create a SoftSerial Objet
SoftwareSerial speakjet = SoftwareSerial(0, txPin);

//The message array contains the command for sounds to be sent
//in order to inunciate the words. Check the SpeakJet Manual for more information
//on producing different words

//                   robots
char message[] = {21, 127, 148, 7, 137, 7, 164, 8, 171, 8, 135, 8, 193, 7, 188};

void setup()  
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

void loop()
{  
  //Send message to the SpeakJet module
  speakjet.print(message);
  while(1);
}

