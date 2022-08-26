 int pwma = 3;      // Power pin for A
int dira = 12;     // Direction pin for A
int pwmb = 11;     // Power pin for B
int dirb = 13;     // Direction pin for B

void setup() {
 // Initializes all of the variables
  pinMode(dira, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(dirb, OUTPUT);
}

void loop() {
 // Note: The power output can go from 0 (not driving) to 255 (full power).
  // Note 2: The direction output can be set as either HIGH or LOW for
  // either wheel. HIGH means that the wheel is going forward,
  // and LOW means that the wheel is going backward. Setting one wheel to HIGH
  // and one wheel to LOW will result in the car turning.
 
  // Tells the car to drive forward, on full power.
  digitalWrite(dira, HIGH);
  analogWrite(pwma, 255);
  digitalWrite(dirb, HIGH);
  analogWrite(pwmb, 255);
  // Waits for one second (1000 milliseconds) until taking further commands.
  delay(1000);
  // Tells the car to stop, by changing both power outputs to zero.
  digitalWrite(dira, HIGH);
  analogWrite(pwma, 0);
  digitalWrite(dirb, HIGH);
  analogWrite(pwmb, 0);
  // Waits for one second until restarting from the beginning of the loop.
  delay(1000);
}
