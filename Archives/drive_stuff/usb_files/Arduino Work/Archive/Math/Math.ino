int a = 3;
int b = 10;
int c = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println(" ");
  Serial.println("Here is some math: ");

  Serial.print("a = ");
  Serial.println(a);
  Serial.print("b = ");
  Serial.println(b);
  Serial.print("c = ");
  Serial.println(c);

  Serial.print("a + b = "); //addition
  Serial.println(a + b);

  Serial.print("a * c = "); //multiplication
  Serial.println(a * c);

  Serial.print("b / a = "); //division
  Serial.println(b / a);

  Serial.print("b - c = "); //subtraction
  Serial.println(b - c);
}

void loop() {
  // put your main code here, to run repeatedly:

}
