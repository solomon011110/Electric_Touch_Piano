#include <Wire.h>

void AQM::writeCMD(byte cmd){
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x00);
  Wire.write(cmd);
  Wire.endTransmission();
}

void AQM::writeChar(byte c){
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x40);
  Wire.write(c);
  Wire.endTransmission();
}

void AQM::writeString(String s){
  Wire.beginTransmission(LCD_ADDR);
  Wire.write(0x40);
  for(int i = 0; i < s.size(); i++){
    Wire.write(s[i]);
    delay(1);
  }
  Wire.endTransmission();
}

void AQM::init(int row){
  Wire.begin();
  delay(50);

  writeCMD((row == 1) ? 0x34 : 0x38);
  delay(1);

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
  byte xAddr = x & 0x07;
  byte yAddr = (y == 0) ? 0x00 : 0x40;
  writeCMD(0x80 | yAddr | xAddr);
}