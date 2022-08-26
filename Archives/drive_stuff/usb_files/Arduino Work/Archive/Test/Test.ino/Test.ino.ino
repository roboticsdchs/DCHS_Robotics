int pin = 15;
long pulse, distance;

void setup() {
 Serial.begin(9600);
}

void loop() {
 pinMode(pin, INPUT);
 
 pulse = pulseIn(pin, HIGH);
 distance = pulse/147;
 
 Serial.println(distance);
 
 delay(1500);
}
