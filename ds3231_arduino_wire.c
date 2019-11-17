#include <Wire.h>

void setup()
{
  Wire_begin();
  Serial_begin(9600);
  /*
   * set the time
  Wire_beginTransmission(0x68);
  Wire_write(0x05);
  int vall = 11;
  int d = (vall/10*16) + (vall%10);
  Wire_write(d);
  Wire_endTransmission();
  */
}

void loop()
{
  Wire_beginTransmission(0x68);
  Wire_write(0x00);
  Wire_endTransmission();
  Wire_requestFrom(0x68, 6);
Serial_println_s("+--------------------+");
char ss = Wire_read();
char mm = Wire_read();
char hh = Wire_read();
char zz = Wire_read();
char dd = Wire_read();
char mo = Wire_read();
int mouth = (mo/16*10) + (mo%16);
int data = (dd/16*10) + (dd%16);
int hour = (hh/16*10) + (hh%16);
int minute = (mm/16*10) + (mm%16);
Serial_print_s("now is:");
Serial_print_i(mouth);
Serial_print_s("-");
Serial_print_i(data);
Serial_print_s(":::");
Serial_print_i(hour);
Serial_print_s(":");
Serial_print_i(minute);
Serial_println_s("---");
  delay(50);
}
