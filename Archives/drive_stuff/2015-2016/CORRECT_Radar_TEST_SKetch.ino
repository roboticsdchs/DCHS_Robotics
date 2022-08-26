#include <Servo.h>

const int pwPin1 = 1;
float sensor, ft;
int pos = 30;
bool switcher = 0;

Servo myservo;

void setup() {
  Serial.begin(9600);
  pinMode(pwPin1, INPUT);
  myservo.attach(0);
  myservo.write(pos);
}

// NOTE: The best speed I can get out of this is 1.5 seconds
// per half rotation. This means that it will take one
// reading every 6 degrees.

// NOTE 2: For the EZ3, the conversion is 57.874 uS/cm.

void loop() {
  int timer = millis();
  if (pos == 150)
    switcher = 1;
  else if (pos == 30)
    switcher = 0;
  if (timer % 50 == 0) {
    if (switcher == 0) {
      pos = pos + 6;
      myservo.write(pos);
    }
    else if (switcher == 1) {
      pos = pos - 6;
      myservo.write(pos);
    }
    ft = (pulseIn(pwPin1, HIGH) / 57.874);
    if (ft < 600) {
      Serial.print(ft);
      Serial.print(" cm");
      Serial.print("     ");
      Serial.print(pos);
      Serial.println(" degrees");
    }
    else if (ft >= 600)
      Serial.println("TOO HIGH");
  }
}
