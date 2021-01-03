int trigger_pin = 2;
int echo_pin = 3;

int time; 
int distance;

void setup() {

  Serial.begin (9600);
  pinMode (trigger_pin, OUTPUT);
  pinMode (echo_pin, INPUT);

}  
void loop() {
  
  digitalWrite (trigger_pin, LOW);
  delayMicroseconds(10);
  digitalWrite (trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  time=pulseIn(echo_pin,HIGH);
  distance=time*0.01330/2;

  Serial.print("Distance:");
  Serial.println(distance);
    
}
