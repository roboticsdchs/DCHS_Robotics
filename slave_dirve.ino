int moveport = 9;
int turnport = 10;
#include <Servo.h>


//test to see if distances are the proper ones

Servo turnmotor;
Servo movemotors;
void setup() {
  Serial.begin(9600)
  turnmotor.attach(turnport);
  movemotors.attach(moveport);

}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data 
  }
}
