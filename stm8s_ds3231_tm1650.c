#include <Wire.h>
#include <stm8s_iwdg.h>
uint8_t num[20] = {
  //0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f,
  0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef
};
void setup()
{
  /*
     start the watch dog
  */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//允许操作独立看门狗
  IWDG_SetPrescaler(IWDG_Prescaler_128);//看门狗预分频
  IWDG_SetReload(255);//设置看门狗复位时间
  IWDG_Enable();//启动独立看门狗
  Wire_begin();
  Serial_begin(9600);
  /*
    // set the time
    Wire_beginTransmission(0x68);
    Wire_write(0x01);
    int vall = 9;
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
  int mouth1 = (mo / 16);
  int mouth2 = (mo % 16);
  int data1 = (dd / 16);
  int data2 = (dd % 16);
  int hour1 = (hh / 16);
  int hour2 = (hh % 16 );
  int mi = (mm / 16 );
  int minute2 = (mm % 16);
  //Serial_println_i(mouth1);
  /*
     display
  */
  for ( int a = 0; a < 9; a++) {
    Wire_beginTransmission(0x24);
    Wire_write(0x11);
    Wire_endTransmission();
    Wire_beginTransmission(0x34);
    Wire_write(num[hour1]);
    Wire_endTransmission();
    Wire_beginTransmission(0x35);
    Wire_write(num[hour2]);
    Wire_endTransmission();
    Wire_beginTransmission(0x36);
    Wire_write(num[mi]);
    Wire_endTransmission();
    Wire_beginTransmission(0x37);
    Wire_write(num[minute2]);
    Wire_endTransmission();
    for (int j = 0;j<=50;j++){
    IWDG_ReloadCounter();
    delay(10);}
    Wire_beginTransmission(0x24);
    Wire_write(0x11);
    Wire_endTransmission();
    Wire_beginTransmission(0x34);
    Wire_write(num[hour1]);
    Wire_endTransmission();
    Wire_beginTransmission(0x35);
    Wire_write(num[hour2]);
    Wire_endTransmission();
    Wire_beginTransmission(0x36);
    Wire_write(num[mi + 10]);
    Wire_endTransmission();
    Wire_beginTransmission(0x37);
    Wire_write(num[minute2 + 10]);
    Wire_endTransmission();
    for (int j = 0;j<=50;j++){
    IWDG_ReloadCounter();
    delay(10);}
  }
  Wire_beginTransmission(0x24);
  Wire_write(0x11);
  Wire_endTransmission();
  Wire_beginTransmission(0x34);
  Wire_write(num[mouth1]);
  Wire_endTransmission();
  Wire_beginTransmission(0x35);
  Wire_write(num[mouth2]);
  Wire_endTransmission();
  Wire_beginTransmission(0x36);
  Wire_write(num[data1]);
  Wire_endTransmission();
  Wire_beginTransmission(0x37);
  Wire_write(num[data2]);
  Wire_endTransmission();
 for (int j = 0;j<=50;j++){
    IWDG_ReloadCounter();
    delay(10);}
}
