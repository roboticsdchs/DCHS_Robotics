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
int leftangle = 113;//for 45 degree angle minus 8
int center = 119;
int rightangle = 139; //for 45 degree angle plus 7
int halfrightangle = 96;
int halfleftangle = 81;
int slightrightangle = 96;
int TrueSpeed;
int Angle;
int moveport = 9;
int turnport = 10;
int park = 1;
const int trigPin0 = 3;
const int echoPin0 = 2;
const int trigPin1 = 5;
const int echoPin1 = 4;
long duration0;//duration for back sensor
int distance0;//duration for the back sensor
long duration1;//distance for the side sensor
int distance1;//duration for the side sensor
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
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  Serial.begin(9600);
  turnmotor.attach(turnport);
  movemotors.attach(moveport);
  turnmotor.write(center);
  
 // while(park==1){
//    sensor0();
//    
//  while(distance0 < 40){
//    Serial.print("forward0");
//    Forward();
//    sensor0();
//    Serial.println(distance0);
//    }
//  sensor0();
//    while(distance0 > 40){
//      Serial.print("forward1");
//      Forward();
//      sensor0();
//      Serial.println(distance0);
//    
//    }
//    sensor0();
//     while(distance0 < 40){
//      Serial.print("backward0");
//   Backward(5);
//sensor0();
//Serial.println(distance0);
//    }
 turnmotor.write(rightangle);
 Backward(6650);
 turnmotor.write(center);
//  Backward(1600);
//  sensor1();
//  while(distance0>25){
//    sensor0();
//  ReverseLeft();
    //}
    Stop();
    colorWipeStrip(strip.Color(  255,   0, 0), 50); // Red
    colorWipeWheel(wheel.Color(  255,   0, 0), 50); // Red 
    delay(5000);
    
    //parked light on
//}
}
void loop() {

}
void Forward() {
  TrueSpeed = 254;
  movemotors.write(110);
  delay(5);
}
void Backward(int backtime) {
  Serial.println("Backward for: ");
  Serial.print(backtime);
  TrueSpeed = 127;
  movemotors.write(70);
  delay(backtime);
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
// void SlightRight() {
//  TrueSpeed = 254;
//  movemotors.write(110);
//  turnmotor.write(slightrightangle);
//  delay(5000);
//  turnmotor.write(center);
//  }
void Right() {
  TrueSpeed = 254;
  movemotors.write(110);
  turnmotor.write(rightangle);
  delay(5000);
  turnmotor.write(center);
}
void ReverseRight() {
  TrueSpeed = 127;
  movemotors.write(70);
  turnmotor.write(rightangle);
  delay(2500);
  turnmotor.write(center);
}
void ReverseLeft() {
  TrueSpeed = 127;
  movemotors.write(110);
  turnmotor.write(leftangle);
  delay(2500);
  turnmotor.write(center);
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
void sensor0(){
//  digitalWrite(pin,HIGH);
// Clears the trigPin
digitalWrite(trigPin0, LOW);
//digitalWrite(trigPin2, LOW);
//digitalWrite(trigPin3, LOW);



delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin0, HIGH);
//digitalWrite(trigPin2, HIGH);
//digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin0, LOW);
//digitalWrite(trigPin2, LOW);
//digitalWrite(trigPin3, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration0 = pulseIn(echoPin0, HIGH);
//duration2 = pulseIn(echoPin2, HIGH);
//duration3 = pulseIn(echoPin3, HIGH);
// Calculating the distance
distance0= duration0*0.034/2;
//distance2= duration2*0.034/2;
//distance3= duration3*0.034/2;
Serial.print("Sensor 1: ");
Serial.println(distance0);

//Serial.print("Sensor 3: ");
//Serial.println(distance2);
//Serial.print("Sensor 4: ");
//Serial.println(distance3);
delay(10);

}
void sensor1(){
//  digitalWrite(pin,HIGH);
// Clears the trigPin
digitalWrite(trigPin1, LOW);
//digitalWrite(trigPin2, LOW);
//digitalWrite(trigPin3, LOW);



delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
//digitalWrite(trigPin2, HIGH);
//digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
//digitalWrite(trigPin2, LOW);
//digitalWrite(trigPin3, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin1, HIGH);
//duration2 = pulseIn(echoPin2, HIGH);
//duration3 = pulseIn(echoPin3, HIGH);
// Calculating the distance
distance1= duration1*0.034/2;
//distance2= duration2*0.034/2;
//distance3= duration3*0.034/2;
Serial.print("Sensor 2: ");
Serial.println(distance1);
//Serial.print("Sensor 3: ");
//Serial.println(distance2);
//Serial.print("Sensor 4: ");
//Serial.println(distance3);
delay(10);

}
