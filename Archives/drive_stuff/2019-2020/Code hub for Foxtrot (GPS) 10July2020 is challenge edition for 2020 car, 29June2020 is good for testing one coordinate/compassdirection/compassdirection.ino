int brg = 0;
int hd = 70;
int comp = 70; 


double turnheading(float heading1, float  bearing){
  int degree1 = bearing - heading1; 
  if (heading1 == bearing) { 
    return Serial.println("0"); 
  } 
    else if (-60 < degree1 < 60) {
      return Serial.println(degree1); 
    }
    else if(degree1 > 60){
        return Serial.println("60");
    }
    else if (degree1 < -60){
      return Serial.println("-60"); 
    }
    
  }
double turncompass(float compass1, float bearing2){
  int degree2 = bearing2 - compass1;
 
  if(compass1 == bearing2){ 
    return Serial.println("turn 0");
  }
    if(-60 < degree2 < 60) {
      return Serial.println(degree2); 
       
  }
    else if(degree2 > 60){
        return Serial.println("turn 60");
        
    }
    else if(degree2 < -60) {
      return Serial.println("turn -60"); 

    }
  }
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  turncompass(hd, brg);
  turnheading(comp, brg);

}
