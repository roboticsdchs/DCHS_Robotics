/*
  Button - Message Sending
  led short side = negative
 */

// constants won't change. It's used here to 
// set the pin number:
const int buttonPin = 2;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int led = 12;
int yed = 11;

void setup() {
  pinMode(buttonPin, INPUT);   // initialize the pushbutton pin as an input:  
  Serial.begin(9600);          // initialize the serial communication:
  pinMode (led, OUTPUT);
  pinMode (yed, OUTPUT);
}

void loop(){
  delay(100);
  buttonState = digitalRead(buttonPin);  // read the state of the pushbutton value:
  if (buttonState == HIGH) {             // check if the pushbutton is pressed. 
    Serial.println("On");    // send a message to the computer:    
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(yed, HIGH);
    delay(100);
    digitalWrite(yed, LOW);
  } 
  else {                                 // If the button is not pressed
    Serial.println("Off");           // send a message to the computer:
    digitalWrite(led, LOW);
    delay(100);
    digitalWrite(yed, LOW);
  }

}
