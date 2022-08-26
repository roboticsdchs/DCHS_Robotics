// does not work as of 12/8/12
// will improve at a later date
const int button = 2;
int serial = 0;
int buttonstate;

void setup () {
 pinMode (button, INPUT);
 Serial.begin(9600);

}

void loop () {
  for (int led = 12; led >= 10; led = led-1) {
    
    
    pinMode (led,OUTSerial.begin(9600);PUT);
    digitalWrite (led, HIGH);
    delay (1000);
    digitalWrite (led, LOW);
    
    digitalRead (button);
    buttonstate = digitalRead (button);
    
    
    while (buttonstate == 1) {
     digitalWrite (led, LOW); 
     digitalRead (button);
     buttonstate = digitalRead (button);
     
     if (led == 12) {
     Serial.println ("you win");  
     delay (10000);
    }
     else {
     Serial.println ("you lose");
     delay (10000);
    }
    
    }
    
  }
  
}
 

