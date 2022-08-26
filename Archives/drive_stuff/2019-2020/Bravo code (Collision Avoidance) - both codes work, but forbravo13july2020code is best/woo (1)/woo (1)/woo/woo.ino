#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_STRIP_PIN    6
#define LED_WHEEL_PIN    7
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 100
Adafruit_NeoPixel strip(LED_COUNT, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel wheel = Adafruit_NeoPixel(12, LED_WHEEL_PIN, NEO_GRB + NEO_KHZ800);
#include <Adafruit_Sensor.h>
int leftangle = 108;
int center = 119;
int rightangle = 139;
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;

int pin = 8;
const int trigPin = 3;
const int echoPin = 2;
long duration;
int distance;

#include <Servo.h>;

Servo turnmotor;
Servo movemotors;
void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  wheel.begin();
  wheel.setBrightness(50);
  wheel.show(); // Initialize all pixels to 'off'
  pinMode(trigPin, OUTPUT);
//  pinMode(pin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);


  
  bravo();
  //movemotors.write(90);
  //turnmotor.write(center);
}


void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(500);
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
int sensor(){
  //digitalWrite(pin, HIGH);
  //clears trig pin
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  //sets the trigpin in high state for 10 micro seconds
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //reads the echopin, return the soundwave travel time in microsecond
  duration = pulseIn(echoPin, HIGH);
  //calculating the distance
  distance = duration*0.034/2;
  //delay(10);
  return distance;
}

int findSmallest() {
  int small = 500;
  for(int i = 0; i < 5; i++){
    int d = sensor();
    if(d < small){
      small= d;
    }
    delay(1);
  }
  return small;
}
void loop() {
  //Serial.println(findMedian());
  //turnmotor.write(90);
}
void alpha() {

}

void bravo() {
  int startTime = millis();
  while(findSmallest()>150 && (millis()<startTime + 21000)){
//    Forward();
Serial.print("Forward");
Serial.print(distance);
  }
   colorWipeStrip(strip.Color(  0,   0, 255), 50); // Blue
    colorWipeWheel(wheel.Color(  0,   0, 255), 50); // Blue 
  Stop();
}
void colorWipeStrip(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void colorWipeWheel(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
