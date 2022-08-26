
int speak = 2;
// the setup function runs once when you press reset or power the board
void setup() {
  messageplay ();
}

// the loop function runs over and over again forever
void loop() {
 
}

void messageplay () {
  pinMode(speak, OUTPUT);
  tone(speak, 327, 1000);
  delay(1000);
}
