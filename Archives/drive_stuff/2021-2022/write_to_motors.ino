void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  String str_in;
  if (Serial.available() > 0) {
    str_in = Serial.readStringUnitl('\n');
  }

  const char *str = str_in; // assume this string is result read from serial
  int servo_port;
  int drive_port;
  int servo_pwm;
  int drive_pwm;
  
  if (sscanf(str, "%d,%d,%d,%d", &servo_port, &drive_port, &servo_pwm, &drive_pwm) == 4) {
      analogWrite(servo_port, servo_pwm);
      analogWrite(drive_port, drive_pwm);
  }
  //get values from serial in for servo and pwm 
  // pwm write the values
}
