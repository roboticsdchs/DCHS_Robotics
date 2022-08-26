#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
byte potPin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin 
int servoVal; // value sent to servo motor
byte servoPin = 9; // pin for servo motor

// motor control
byte inA = 4;
byte pwmA = 5;
//byte pwmB = 6;
//byte inB = 7;
 
void setup() 
{ 
  pinMode(inA, OUTPUT); //motor pin A
  //pinMode(inB, OUTPUT); //motor pin B
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
  
  Serial.begin(9600); 
} 
 
void loop() 
{
  digitalWrite(inA, LOW); // LOW = forward
  analogWrite(pwmA, 75);
  
  val = analogRead(potPin);            // reads the value of the potentiometer (value between 0 and 1023) 
  servoVal = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(servoVal);                  // sets the servo position according to the scaled value 
  Serial.println(val);
  Serial.println(servoVal);
  delay(15);                           // waits for the servo to get there 
} 
