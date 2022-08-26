/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
   
   if you are going to add another light add a resistor of 220 or 330. 330 is orange orange brown
 */
 
// varibles
int led = 10;
int led2= 9;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(800);  // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(600);  // wait for a second
  
  digitalWrite (led2, HIGH);
  delay (800);
  digitalWrite(led2, LOW);
  delay (600);
}
