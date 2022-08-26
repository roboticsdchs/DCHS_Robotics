const int hallPinRight = 13; // hall effect sensor 1
int hallStateRight = 0; // "Button" variable #1 for right wheel
int HSRR; // "Button" variable #2 for right wheel
float hallRightCounter = 0; // State change counter for right wheel
float HRC1 = 0; // Distance covered by right wheel

const int hallPinLeft = 12; // hall effect sensor 2
int hallStateLeft = 0; // "Button" variable #1 for left wheel
int HSRL; // "Button" variable #2 for left wheel
float hallLeftCounter = 0; // State change counter for left wheel
float HLC1 = 0; // Distance covered by left wheel

void setup() {
  Serial.begin(9600);

  pinMode(hallPinRight, INPUT);
  pinMode(hallPinLeft, INPUT);
  HSRR = digitalRead(hallPinRight);
  HSRL = digitalRead(hallPinLeft);

}

void loop() {
  hallStateRight = digitalRead(hallPinRight);
  hallStateLeft = digitalRead(hallPinLeft);
 //Serial.print(hallStateRight); Serial.print("    "); Serial.println(hallStateLeft);
  if (hallStateRight != HSRR) {
    if (hallStateRight == LOW) {
      hallRightCounter++;
      HRC1 = ((hallRightCounter / 16) * 89);
      Serial.print("Right Distance: ");
      Serial.print(hallRightCounter);
      Serial.print("   Left Distaance: ");
      Serial.println(hallLeftCounter);
    }
  }

  if (hallStateLeft != HSRL) {
    if (hallStateLeft == LOW) {
      hallLeftCounter++;
      HLC1 = ((hallLeftCounter / 16) * 89);
      Serial.print("Right Distance: ");
      Serial.print(hallRightCounter);
      Serial.print("   Left Distaance: ");
      Serial.println(hallLeftCounter);
    }
  }
}
