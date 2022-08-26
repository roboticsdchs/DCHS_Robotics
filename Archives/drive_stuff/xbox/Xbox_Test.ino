#include <XBOXRECV.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

USB Usb;
XBOXRECV Xbox(&Usb);

#define ForwardLight 5
#define BackwardLight 6
#define TurnLight 6

/* Define the rotational speed of the motor. MUST be between 0 and 255. */
int pulse = 0;
int forward = 0;
int brake_on = 0;


void setup() {
  TCCR1B = TCCR1B & 0b11111000 | 0x02;
  Serial.begin(9600);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  pinMode (ForwardLight, OUTPUT);
  pinMode (BackwardLight, OUTPUT);
  pinMode (TurnLight, OUTPUT);
  
}

void loop() {
  Usb.Task();
  if(Xbox.XboxReceiverConnected) 
    {
    for(uint8_t i=0;i<4;i++) 
      {
      if(Xbox.getButtonPress(L2, i))
        {
        Serial.print("L2: ");
        Serial.println(Xbox.getButtonPress(L2, i));
        pulse = Xbox.getButtonPress(L2, i);
        analogWrite(BackwardLight, Xbox.getButtonPress(L2, i));
        analogWrite(ForwardLight, 0);
        }
        
      if(Xbox.getButtonPress(R2, i))      
        {
        Serial.print("R2: ");
        Serial.println(Xbox.getButtonPress(R2, i));
        pulse = Xbox.getButtonPress(R2, i);
        forward = 1;
        analogWrite(ForwardLight, Xbox.getButtonPress(R2, i));
        analogWrite(BackwardLight, 0);
        }
        
       if(Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500) 
         {
          if(Xbox.getAnalogHat(LeftHatX, i) > 7500)
            {
            Serial.print(F("LeftHatX: ")); 
            Serial.print(Xbox.getAnalogHat(LeftHatX, i));
            Serial.print("\t");
            }
        if (Xbox.getAnalogHat(LeftHatX, i) < -7500)
          {
          Serial.print(F("LeftHatX: ")); 
          Serial.print(Xbox.getAnalogHat(LeftHatX, i));
          Serial.print("\t");
          
        }
        
        if(Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500) 
          {
          Serial.print(F("LeftHatY: ")); 
          Serial.print(Xbox.getAnalogHat(LeftHatY, i));
          Serial.print("\t");
          }
          Serial.println();
         }
    
      if(Xbox.getButtonClick(UP, i)) 
        {
        Serial.println(F("Up"));
        }
        
      if(Xbox.getButtonClick(DOWN, i)) 
        {
        Serial.println(F("Down"));
        }
        
      if(Xbox.getButtonClick(LEFT, i)) 
        {
        Serial.println(F("Left"));
        }
        
      if(Xbox.getButtonClick(RIGHT, i)) 
        {
        Serial.println(F("Right"));
        }

      if(Xbox.getButtonClick(START, i)) 
        {
        Serial.println(F("Start"));
        }
    
      if(Xbox.getButtonClick(BACK, i)) 
        {
        Serial.println(F("Back"));
        }
      
      if(Xbox.getButtonClick(L3, i))
        Serial.println(F("L3"));
        
      if(Xbox.getButtonClick(R3, i))
        Serial.println(F("R3"));

      if(Xbox.getButtonClick(L1, i))
        Serial.println(F("L1"));
        
      if(Xbox.getButtonClick(R1, i))
        Serial.println(F("R1"));
        
      if(Xbox.getButtonClick(XBOX, i)) 
        {
        Xbox.setLedMode(ROTATING, i);
        Serial.println(F("Xbox"));        
        }

      if(Xbox.getButtonClick(A, i))
        {
        Serial.println(F("A"));
      }
      
    if(Xbox.getButtonClick(B, i))
      {
      Serial.println(F("B"));
      brake_on = 1;
      pulse = 100;
      
    if(Xbox.getButtonClick(X, i))
      Serial.println(F("X"));
      
    if(Xbox.getButtonClick(Y, i))
      {
      Serial.println(F("Y"));
      }
    }
  } 
  delay(1);
}
    }
