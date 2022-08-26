#include "math.h"

float a = 5.98;
float b;
float c = 20.4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Lets find our unknown side");
  
  if (a==0)
  {
    a = sqrt(c*c - b*b);
  }
  
  if (b==0)
  { 
    b = sqrt(c*c - a*a);
  }
  
  if (c==0)
  {
    c = sqrt(a*a + b*b);
  }
  
  Serial.print("a = ");
  Serial.println(a);
  
  Serial.print("b = ");
  Serial.println(b);
  
  Serial.print("c = ");
  Serial.println(c);
}

void loop() {
  // put your main code here, to run repeatedly:

}
