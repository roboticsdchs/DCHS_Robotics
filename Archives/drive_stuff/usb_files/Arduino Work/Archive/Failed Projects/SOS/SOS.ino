/* Planned to be an automatic SOS signal
Incomplete abandoned project
*/
int led = 11;

void setup () {
 pinMode (led, OUTPUT);
}

void loop () {
 if 
 digitalWrite(led, HIGH);
 delay(5000);
 digitalWrite(led, LOW); 
 delay(5000);
 
 digitalWrite(led, HIGH);
 delay(1000);
 digitalWrite(led, LOW);
 delay(1000);
 
 digitalWrite(led, HIGH);
 delay(5000);
 digitalWrite(led, LOW);
 delay(5000);
}
