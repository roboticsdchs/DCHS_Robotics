int i;
int val;
int redpin=0;
void setup() {
    pinMode(redpin,OUTPUT);
    Serial.begin(9600);
}
void loop() {
    i=analogRead(redpin);
    val=(6762/(i-9))-4;
    Serial.println(val);
}

// Longwise- Begins sensing ~ 90+/-15 Degrees, Accurate at 90+/-5 Degrees
// Shortwise- Begins sensing ~90 +/-10 Degrees, Accurate at 90+/-2 Degrees
