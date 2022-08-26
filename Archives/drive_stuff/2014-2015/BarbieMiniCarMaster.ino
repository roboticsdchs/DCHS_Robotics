#include <Servo.h> 

Servo turnServo;  //create servo object to control a servo 

// Turning 
byte turnServoPin = 9; //pin for servo motor

// Drive Motor
byte driveMotorDirectionPin = 4;
byte driveMotorSpeedPin = 5;

// Distance Sensors
int FLDistSensorVal;          //value from the distance Front Left sensor
int FLDistSensorPin = 0;   //Front Left Sensor analog pin
int FCDistSensorVal;         //value from the distance Front Right sensor
int FCDistSensorPin = 1;  //Front Center Sensor analog pin
int FRDistSensorVal;         //value from the distance Front Right sensor
int FRDistSensorPin = 2;  //Front Right Sensor analog pin
int distThreshold = 280;    //threshold for the distance sensor

void setup()
{
    //set pins
    pinMode(driveMotorDirectionPin, OUTPUT);
    turnServo.attach(turnServoPin);  //attaches the servo to the servo object

    randomSeed(analogRead(5)); //initialize random seed
    Serial.begin(9600);
}

void loop()
{
    FLDistSensorVal = analogRead(FLDistSensorPin);
    FCDistSensorVal = analogRead(FCDistSensorPin);
    FRDistSensorVal = analogRead(FRDistSensorPin);
    Serial.print(FLDistSensorVal);
    Serial.print(" - ");
    Serial.print(FCDistSensorVal);
    Serial.print(" - ");
    Serial.println(FRDistSensorVal);

    if(FLDistSensorVal < distThreshold && FCDistSensorVal < distThreshold && FRDistSensorVal < distThreshold){
        forward(150);
        straight();
    }
    //else if (FLDistSensorVal > distThreshold && FCDistSensorVal > distThreshold && FRDistSensorVal > distThreshold){
    //    backward(100);
    //    delay(2000);
    //}
    else if(FLDistSensorVal >= distThreshold){  //left
        backward(100);
        delay(100);
        left();
        delay(1000);
    }
    else if(FRDistSensorVal >= distThreshold){  //right
        backward(100);
        delay(100);
        right();
        delay(1500);
    }
    else if(FCDistSensorVal >= distThreshold){  //center
        backward(100);
        delay(100);
        if (turnServo.read() == 66){
            left();
        }
        else if (turnServo.read() == 89){
            right();
        }
        delay(1000);
    }
}

void forward(int velocity){
    digitalWrite(driveMotorDirectionPin, LOW); //LOW is forward
    analogWrite(driveMotorSpeedPin, velocity);
}

void backward(int velocity){
    digitalWrite(driveMotorDirectionPin, HIGH); //HIGH is backward
    analogWrite(driveMotorSpeedPin, velocity);
}

void straight(){
    //get position of turning servo and turn until center
    turnServo.write(79.5);  //turn servo to x degrees
}

void left(){
    turnServo.write(66); //turn servo to x degrees
    //delay(duration)
}

void right(){
    turnServo.write(89); //turn servo to x degrees
    //delay(duration);
}

