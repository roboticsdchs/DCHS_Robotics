#include <SPI.h>
#include <Pixy.h>
#include <Wire.h>
Pixy pixy;
//Int for object tracking
int xpos; 
int width;
//Int for color detection
int Color;
int PreviousColor;
void setup() {
  Wire.begin(3);
  Serial.begin(9600);
  pixy.init();
}
void loop() {
  static int i = 0;
  uint16_t blocks;
  blocks = pixy.getBlocks();
  pixy.getBlocks();
  if(blocks){
    i++;
    if(i%25 == 0){
  if(pixy.blocks[0].signature == 4){
  xpos = pixy.blocks[0].x;
  width = pixy.blocks[0].width;
  int LRtrack = xpos - 160;
  int FBtrack = -(width - 50);
Serial.print(LRtrack);
Serial.print("/");
Serial.print(FBtrack);
  }
   int Color =  pixy.blocks[0].signature;
     if(Color!=PreviousColor){
     if(Color==7) {
      Serial.print("red");
     }
     if(Color==4){
      Serial.print("grn");
     }
     if(Color==3){
      Serial.print("ylw");
     }
     if(Color==2){
      Serial.print("blu");
     }
     PreviousColor = Color;
     }
}
  }
}
