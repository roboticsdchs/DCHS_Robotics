

int heading = 90; //heading provides reference point for servo movement
//int dir = 2;
#include <SPI.h>
#include <Pixy.h>

int temp = -1;

int lCount = 0;

int leftmotorForward = 4;
int leftmotorBackward = 9;
int leftmotorspeed = 5;
int rightmotorForward = 8;
int rightmotorBackward = 7;
int rightmotorspeed = 6;

//speed varibles 

// This is the main Pixy object
Pixy pixy;


void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pixy.init();

  Serial.begin(9600);
  Serial.print("Starting...\n");
servoPulse(90);
  pixy.init();

  delay(1000);

  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(10, OUTPUT);


}



void servoPulse (int angle) // controls servo
{
  int pwm = (angle * 11) + 500;    // Convert angle to microseconds
  digitalWrite(10, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(10, LOW);
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

  // put your main code here, to run repeatedly:
//  servoPulse(heading); //sets servo angle to 90 degrees to equal heading
  delay(5);

  digitalWrite(leftmotorBackward, LOW);
  digitalWrite(rightmotorBackward, LOW);
  digitalWrite(leftmotorForward, HIGH);
  digitalWrite(rightmotorForward, HIGH);
  analogWrite(leftmotorspeed, 40);
  analogWrite(rightmotorspeed, 40);
 // delay(9999

  
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
      //{
        Serial.print(pixy.blocks[0].x );
        Serial.print(" ");
        //        sprintf(buf, "  block %d: ", j);
        //        Serial.print(buf);
        //        pixy.blocks[j].print();
      //}
      Serial.println();

      while (pos > 161)
      {
        if (temp != 1)
        {
          heading = 90;
          servoPulse(heading);
          temp = 1;
        }
        if (heading > 45)
        {
          heading = heading + 2;
        }
        servoPulse(heading);
       blocks = pixy.getBlocks(); //Are we telling it to get blocks too many times? It keeps stopping, why???? $$$$$$$$$$$$
        
        pos = pixy.blocks[j].x;
      }
       while (pos < 156) //while the 'x' value of the object is less than 154 in Pixy Cam...
      {
        if (temp != 0)
        {
          heading = 90;
          servoPulse(heading);
          temp = 0;
        }
        if (heading < 135) //But, while the servo heading is less than 160 degrees so that the servo does not break
        {
          
          heading = heading - 2; //Add one to servo degrees
        }
        servoPulse(heading); //set the servopulse to the new heading
        blocks = pixy.getBlocks(); //Get more blocks
        pos = pixy.blocks[j].x;  //Change the Value of the position to do the process again
      }

    }
  }
}
