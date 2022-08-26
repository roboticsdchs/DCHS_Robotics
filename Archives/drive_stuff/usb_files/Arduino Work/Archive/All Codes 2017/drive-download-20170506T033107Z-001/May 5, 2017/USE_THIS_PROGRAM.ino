
//Drive straight 

#define CW  0

#define CCW 1



// Motor definitions to make life easier:

#define MOTOR_A 0

#define MOTOR_B 1



// Pin Assignments //

// Don't change these! These pins are statically defined by shield layout

const byte PWMA = 3;  // PWM control (speed) for motor A

const byte PWMB = 11; // PWM control (speed) for motor B

const byte DIRA = 12; // Direction control for motor A

const byte DIRB = 13; // Direction control for motor B



int heading = 90; //heading provides reference point for servo movement
//int dir = 2;
#include <SPI.h>
#include <Pixy.h>


//speed varibles 
int aspeed = 127;
int bspeed = 127;
int motorSpeedA = 0;
int motorSpeedB = 0;
int forwardSpeed = 33;
int adir = 1;
int bdir = 1;

// This is the main Pixy object
Pixy pixy;


void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pixy.init();

  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();

  delay(1000);

  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(10, OUTPUT);


}


void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == aspeed)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == bspeed)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

void setupArdumoto()
{
  // All pins should be setup as outputs:

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);

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

  driveArdumoto(MOTOR_A, CW, 25);
  driveArdumoto(MOTOR_B, CW, 25);


  // put your main code here, to run repeatedly:
  servoPulse(heading); //sets servo angle to 90 degrees to equal heading
  delay(5);

  // grab blocks!
  blocks = pixy.getBlocks();
  pos = pixy.blocks[j].x;
  // If there are detect blocks, print them!
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
          heading = heading - 1;
        }
        servoPulse(heading);
        blocks = pixy.getBlocks();
        
        pos = pixy.blocks[j].x;
      }
      while (pos < 154) //while the 'x' value of the object is less than 154 in Pixy Cam...
      {
        if (heading < 135) //But, while the servo heading is less than 160 degrees so that the servo does not break
        {
          heading = heading + 1; //Add one to servo degrees
        }
        servoPulse(heading); //set the servopulse to the new heading
        blocks = pixy.getBlocks(); //Get more blocks
        pos = pixy.blocks[j].x;  //Change the Value of the position to do the process again
      }

    }
  }
}
