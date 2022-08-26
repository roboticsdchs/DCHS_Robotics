  int Speed = 30;
  int TrueSpeed;
void setup() {

pinMode(9, OUTPUT);
}

void loop() {
  TrueSpeed = Speed + 191;
    analogWrite(9, TrueSpeed);
}

//254 = Full Forward
//191 = Stop
//127 = Full Backwards
//+-14 = Barely Moving
//+-30 = Reasonable Speed
