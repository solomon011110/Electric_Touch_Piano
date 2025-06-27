#include "AQM.h"
#include <Wire.h>

void AQM::writeCMD(unsigned char cmd){
  int c = cmd;
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x00);
  Wire.write(c);
  Wire.endTransmission();
}

void AQM::writeChar(unsigned char c){
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x40);
  Wire.write(c);
  Wire.endTransmission();
}

void AQM::writeString(String s){
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x40);
  for(int i = 0; i < s.length(); i++){
    Wire.write(s[i]);
  }
  Wire.endTransmission();
}

void AQM::init(){
  Wire.begin();
  delay(50);

  for(int i = 0; i < 9; i++){
    writeCMD(INITCMD[i][0]);
    delay(INITCMD[i][1]);
  }
}

void AQM::clear(){
  writeCMD(0x01);
  delay(2);
}

void AQM::setCursor(unsigned char x, unsigned char y){
  int xAddr = x & 0x07;
  int yAddr = (y == 0) ? 0x00 : 0x40;
  writeCMD(0x80 | yAddr | xAddr);
}