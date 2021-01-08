/*
formulas
distanceCm= duration*0.034/2;
distanceInch = duration*0.0133/2;
*/

// ultra1
const int trig_pin1;
const int echo_pin1;
long duration1;
int distance1;
void ultra1() { 
  digitalWrite (trigger_pin1, LOW);
  delayMicroseconds(1);
  digitalWrite (trigger_pin1, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigger_pin1, LOW);
  duration1=pulseIn(echo_pin1,HIGH);
  distance1=duration1*0.01330/2;
  Serial.println("Ultra1:");
  Serial.println(distance1);
  delay(1);
} 

// ultra 2
const int trig_pin2;
const int echo_pin2;
long duration2;
int distance2;
void ultra2() { 
 digitalWrite (trigger_pin2, LOW);
  delayMicroseconds(1);
  digitalWrite (trigger_pin2, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigger_pin2, LOW);
  duration2=pulseIn(echo_pin2,HIGH);
  distance2=duration2*0.01330/2;
  Serial.println("Ultra2:");
  Serial.println(distance2);
  delay(1);
}

// ultra 3
const int trig_pin3;
const int echo_pin3;
long duration3;
int distance3;
void ultra1() { 
  digitalWrite (trigger_pin3, LOW);
  delayMicroseconds(1);
  digitalWrite (trigger_pin3, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigger_pin3, LOW);
  duration3=pulseIn(echo_pin3,HIGH);
  distance3=duration3*0.01330/2;
  Serial.println("Ultra3:");
  Serial.println(distance3);
  delay(1);
}

void setup() {
  Serial.begin (19200);
  pinMode (trigger_pin1, OUTPUT);
  pinMode (echo_pin1, INPUT);
  pinMode (trigger_pin2, OUTPUT);
  pinMode (echo_pin2, INPUT);
  pinMode (trigger_pin3, OUTPUT);
  pinMode (echo_pin3, INPUT);
}  

void loop() {
  ultra(1,2);
  ultra(3,4);
  ultra(5,6);
}
