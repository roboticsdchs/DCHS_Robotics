// constants won't change. They're used here to set pin numbers:
const int hallPin = 9;     // the number of the hall effect sensor pin
// variables will change:
int hallState = 0;          // variable for reading the hall sensor status
int previousState = 0;
int teeth = 0;

void setup() {
  // initialize the hall effect sensor pin as an input:
  pinMode(hallPin, INPUT);     
  Serial.begin(9600);
}

void loop(){
  // read the state of the hall effect sensor:
  hallState = digitalRead(hallPin);
  if (hallState != previousState){
    teeth++;
    previousState=hallState;
  }

  Serial.println(teeth);
}

