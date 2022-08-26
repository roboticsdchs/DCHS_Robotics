int TrueSpeed;
int Angle;

void setup() {
  pinMode(9, OUTPUT); //motor
  pinMode(7, OUTPUT); //servo (I hope)

}


void Forward() {
  TrueSpeed = 254;
  analogWrite(9, TrueSpeed);
  delay(5000);
}
void Backward() {
  TrueSpeed = 127;
  analogWrite(9, TrueSpeed);
  delay(5000);
}
  void Stop() {
    TrueSpeed = 191;
    analogWrite(9, TrueSpeed);
    delay(5000);
  }
  void Left() {
    TrueSpeed = 254;
    analogWrite(9, TrueSpeed);
    Angle = 85;
    analogWrite(7, 85);
    delay(5000):
    }

    void Right() {
    TrueSpeed = 254;
    analogWrite(9, TrueSpeed);
    Angle = 100;
    analogWrite(7, 100);
    delay(5000):
    }






  void loop() {
}
