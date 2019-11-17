#include <Wire.h>

void setup()
{
  Wire_begin();
  Serial_begin(9600);
}

void loop()
{
  Wire_beginTransmission(0x68);
  Wire_write(0x00);
  Wire_endTransmission();
  Wire_requestFrom(0x68, 1);
Serial_println_s("+--------------------+");
    char val = Wire_read();
    int c = (val/16*10) + (val%16) ;
     Serial_println_i(c);
  delay(500);
}
