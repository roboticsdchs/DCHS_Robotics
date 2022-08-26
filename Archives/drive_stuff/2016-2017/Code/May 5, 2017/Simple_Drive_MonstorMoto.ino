void setup() {
 for (int i = 4; i<10; i++)
 {
  pinMode(i,OUTPUT);
 }
 analogWrite(5, 25);
// analogWrite(6, 25);
}

void loop() {
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(9, LOW);
  

}
