#include "math.h"

float a = 2;
float b = 4;
float c;

void setup() {
  Serial.begin(9600);
  
  Serial.println("Lets calcuate a hypotenuse");
  
  Serial.print("a = ");
  Serial.println(a);
  
  Serial.print("b =");
  Serial.println(b);
  
  c = sqrt( a*a + b*b );
  
  Serial.print("c =");
  Serial.println(c);

}

void loop() {
  
  
  
}
