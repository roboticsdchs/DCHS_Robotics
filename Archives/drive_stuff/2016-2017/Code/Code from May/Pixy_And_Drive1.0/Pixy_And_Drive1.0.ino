/*
  Right Motor Drive Pins: 8 & 7, Speed Pin: 6
  Right Encoder Pin: A5
  Left Motor Drive Pins: 4 & 9, Speed Pin: 5
  Left Encoder Pin: A3
  Steering Servo Pin: 10
  Distance Sensor Aiming Servo Pin: 11
  Front Distance Sensor Pin: A2
  Rear Distance Sensor Pin: A1
  Front Hall Effect Sensor Toggle Pin: 12
*/

int heading = 90; //heading provides reference point for servo movement
//int dir = 2;
#include <SPI.h>
#include <Pixy.h>


//enables RedBot for use with encoders
#include <RedBot.h>
RedBotMotors motors;
RedBotEncoder encoder = RedBotEncoder(A3, A5);  // initializes encoders
int countsPerRev = 192;   // 4 pairs of N-S x 48:1 gearbox = 192 ticks per wheel rev
// variables used to store the left and right encoder counts.
int lCount;
int rCount;

//sets pins used for moters
int leftmotorForward = 4; // left motor (+) green wire
int leftmotorBackward = 9; // left motor (-) black wire
int leftmotorspeed = 5; // left motor speed signal
int rightmotorForward = 8; // right motor (+) green wire
int rightmotorBackward = 7; // right motor (-) black
int rightmotorspeed = 6; // right motor speed signal


//speed varibles

// This is the main Pixy object
Pixy pixy;


void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pixy.init();

  Serial.begin(9600);
  Serial.print("Starting...\n");

  Serial.println("___________________________________");
  pinMode(leftmotorForward, OUTPUT);
  pinMode(leftmotorBackward, OUTPUT);
  pinMode(leftmotorspeed, OUTPUT);
  pinMode(rightmotorForward, OUTPUT);
  pinMode(rightmotorBackward, OUTPUT);
  pinMode(rightmotorspeed, OUTPUT);

  pixy.init();

  delay(1000);
}



void servoPulse (int angle) // controls servo
{
  int pwm = (angle * 11) + 500;    // Convert angle to microseconds
  digitalWrite(2, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(2, LOW);
  delay(50);                   // Refresh cycle of servo
}


void loop()
{
  static int i = 0;
  int pos;
  int j;
  uint16_t blocks;
  char buf[32];
  int pwm = (heading * 11) + 500;    // Makes PWM a Global Variable. See below for PWM definition

  servoPulse(heading); //sets servo angle to 90 degrees to equal heading
  delay(5);

  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 40);
  analogWrite(rightmotorspeed, 40);

  // grab blocks!
  blocks = pixy.getBlocks();
  pos = pixy.blocks[j].x; // If there are detect blocks, print them!
  if (blocks)
  {
    if (i % 50 == 0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      //for (j = 0; j < blocks; j++)
      {
        Serial.print(pixy.blocks[0].x );
        Serial.print(" ");
        //        sprintf(buf, "  block %d: ", j);
        //        Serial.print(buf);
        //        pixy.blocks[j].print();
      }
      Serial.println();

      while (pos > 163)
      {
        if (heading > 45)
        {
          heading = heading - 3;
        }
        servoPulse(heading);
        blocks = pixy.getBlocks();

        pos = pixy.blocks[j].x;
      }
      while (pos < 154) //while the 'x' value of the object is less than 154 in Pixy Cam...
      {
        if (heading < 135) //But, while the servo heading is less than 160 degrees so that the servo does not break
        {
          heading = heading + 3; //Add one to servo degrees
        }
        servoPulse(heading); //set the servopulse to the new heading
        blocks = pixy.getBlocks(); //Get more blocks
        pos = pixy.blocks[j].x;  //Change the Value of the position to do the process again
      }

    }
  }
}
