#include <Adafruit_NeoPixel.h>

int Speed = 110;
int leftangle = 78;
int center = 86;
int rightangle = 93;
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
int tPin = 11;
int ePin = 6;
long duration, cm;
#include <Servo.h>
#define PIN      5
#define N_LEDS 144
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

Servo turnmotor;
Servo movemotors;
void setup() {
  Serial.begin(9600);
  pinMode(tPin, OUTPUT);
  pinMode(ePin, INPUT);
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
}

void loop() 
  {
    Distance();
    if(cm<30){
      movemotors.write(90);
    }
    else{
      movemotors.write(Speed);
      
    }
}


void Distance(){
  digitalWrite(tPin, LOW);
  delayMicroseconds(5);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(tPin, LOW); //the last five lines of code make the module transmit an ultrasonic pulse.
  duration = pulseIn(ePin, HIGH);  //checks how long it took for the ultrasonic waves to echo back to the receiver.
  cm = duration/2/29.1;   //Converts the value stored in "duration" to centimeters, which will make testing more convenient.
  Serial.println(cm);  //Prints the distance measured to the serial monitor.
  delay(100);//this just makes the serial print more legible.

}

void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(5000);
}
void Backward() {
  TrueSpeed = 127;
  movemotors.write(70);
  delay(5000);
}
  void Stop() {
    TrueSpeed = 191;
    movemotors.write(90);
    delay(5000);
  }
  void Left() {
    TrueSpeed = 254;
    movemotors.write(110);
    turnmotor.write(leftangle);
    delay(5000);
    turnmotor.write(center);
    }

    void Right() {
    TrueSpeed = 254;
    movemotors.write(110);
    turnmotor.write(rightangle);
    delay(5000);
    turnmotor.write(center);
    }

