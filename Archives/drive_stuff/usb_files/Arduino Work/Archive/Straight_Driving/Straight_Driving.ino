const int hallPinRight = 6; // hall effect sensor 1
int hallStateRight = 0; // "Button" variable #1 for right wheel
int HSRR; // "Button" variable #2 for right wheel
float hallRightCounter = 0; // State change counter for right wheel
float HRCA = 0; // Value that gives the right wheel's velocity
float HRCB = 0; // Value after the loop runs for right wheel
float HRC1 = 0; // Distance covered by right wheel

const int hallPinLeft = 5; // hall effect sensor 2
int hallStateLeft = 0; // "Button" variable #1 for left wheel
int HSRL; // "Button" variable #2 for left wheel
float hallLeftCounter = 0; // State change counter for left wheel
float HLCA = 0; // Value that gives the left wheel's velocity
float HLCB = 0; // Value after the loop runs for left wheel
float HLC1 = 0; // Distance covered by left wheel

unsigned long timer; // Measures the time that has gone by, in milliseconds

int pwma = 3; // Left motor
int dira = 12; // Left motor
int pwmb = 11; // Right motor
int dirb = 13; // Right motor
int rpow = 255; // Changeable power for right wheel
int lpow = 255; // Changeable power for left wheel

void setup() {
  driveSetup();
}

void loop() {
  driveLoop(30, 'F');
  delay(1000);
  driveLoop(20, 'B');
  delay(1000);
  driveLoop(40, 'L');
  delay(1000);
  driveLoop(10, 'R');
  delay(1000);
}

void driveSetup() {
  pinMode(hallPinRight, INPUT);
  pinMode(hallPinLeft, INPUT);
  pinMode(dira, OUTPUT);
  pinMode(pwma, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(dirb, OUTPUT);
  HSRR = digitalRead(hallPinRight);
  HSRL = digitalRead(hallPinLeft);
  Serial.begin(9600);
  analogWrite(pwma, rpow);
  analogWrite(pwmb, lpow);
}

void driveLoop(int distance, char dir) {
  analogWrite(pwma, rpow);
  analogWrite(pwmb, lpow);
  while (HRC1 <= distance)
  {
    // Note #1: Each wheel has a circumference of 7.854 in.
    // Note #2: The ratio of magnet state changes to wheel rotations is 192:1.
    if (dir == 'L')
    {
      digitalWrite(dira, HIGH);
      digitalWrite(dirb, LOW);
    }
    else if (dir == 'R')
    {
      digitalWrite(dira, LOW);
      digitalWrite(dirb, HIGH);
    }
    else if (dir == 'F')
    {
      digitalWrite(dira, HIGH);
      digitalWrite(dirb, HIGH);
    }
    else if (dir == 'B') {
      digitalWrite(dira, LOW);
      digitalWrite(dirb, LOW);
    }

    timer = millis();

    hallStateRight = digitalRead(hallPinRight);
    hallStateLeft = digitalRead(hallPinLeft);
    if (hallStateRight != HSRR) {
      if (hallStateRight == LOW) {
        hallRightCounter++;
        HRC1 = ((hallRightCounter / 192) * 7.854);
      }
    }

    if (hallStateLeft != HSRL) {
      if (hallStateLeft == LOW) {
        hallLeftCounter++;
        HLC1 = ((hallLeftCounter / 192) * 7.854);
      }
    }

    HSRR = hallStateRight;
    HSRL = hallStateLeft;

    // I should probably count separate time intervals, with data
    // getting gathered for both the time and the state changes
    // every given fraction of a second.
    if ((timer % 50) == 0) {
      HRCA = (hallRightCounter - HRCB) / 0.05;
      HLCA = (hallLeftCounter - HLCB) / 0.05;
      Serial.print("R: ");
      Serial.println(HRCA);
      Serial.print("L: ");
      Serial.println(HLCA);
      HRCB = hallRightCounter;
      HLCB = hallLeftCounter;

      if (HRCA < HLCA)
      {
        lpow = lpow + 1;
        analogWrite(pwmb, lpow);
      }
      else if (HRCA > HLCA)
      {
        lpow = lpow - 1;
        analogWrite(pwmb, lpow);
      }
    }
  }
  analogWrite(pwma, LOW);
  analogWrite(pwmb, LOW);
  HRC1 = 0;
  HLC1 = 0;
  hallRightCounter = 0;
  hallLeftCounter = 0;
}

