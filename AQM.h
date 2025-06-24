#include "esp32-hal.h"
#include <Wire.h>
#define LCD_ADDR 0x3E

class AQM{
  private:
  byte INITCMD[8][2] = {
    {0x39, 1},
    {0x14, 1},
    {0x70, 1},
    {0x56, 1},
    {0x6C, 250},
    {0x38, 1},
    {0x0C, 1},
    {0x01, 2}
  };

  public:
  void writeCMD(byte cmd);

  void writeChar(byte c);

  void init(int row);

  void clear();

  void setCursor(unsigned char x, unsigned char y);


}