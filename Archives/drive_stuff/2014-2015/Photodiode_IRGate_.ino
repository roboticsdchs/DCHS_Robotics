int photodiode_pin = 0;
int blocks = 0; //number of times the sensor senses a blockage
int state = 0;

void setup(){
  Serial.begin(9600);
  //pinMode(photodiode_pin,INPUT);
}

void loop(){
 int photodiode_val = analogRead(photodiode_pin); 
 
 
 if (photodiode_val > 700){
   if (state == 0){
     blocks++;
     state = 1;
   }
 }
 
 if(photodiode_val < 700){
   state = 0;
 }
 
 
 Serial.println(blocks);
}
