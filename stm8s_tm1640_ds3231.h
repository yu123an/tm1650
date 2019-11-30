#include <Wire.h>
#include <stm8s_iwdg.h>
int scl = 0;    //PA1
int sda = 1;    //PA2
void i2c_start() {
  digitalWrite(scl, 1);
  delayMicroseconds(2);
  digitalWrite(sda, 1);
  delayMicroseconds(2);
  digitalWrite(sda, 0);
  delayMicroseconds(2);
  digitalWrite(scl, 0);
  delayMicroseconds(2);
}
void i2c_stop() {
  digitalWrite(scl, 0);
  delayMicroseconds(2);
  digitalWrite(sda, 0);
  delayMicroseconds(2);
  digitalWrite(scl, 1);
  delayMicroseconds(2);
  digitalWrite(sda, 1);
  delayMicroseconds(2);
}
void i2c_Write(uint8_t data) {
  pinMode(sda, OUTPUT);
  int t = data;
  int arr[8];
  for (int i = 0; i <= 7; i++) {
    if (data % 2) {
      arr[i] = 1;
    }
    else
    {
      arr[i] = 0;
    }
    data /= 2;
  }
  //if(dot){arr[0] = 1}else{arr[0] = 0}
  // for ( int j = 7; j >= 0; j--) {
  for ( int j = 0; j <= 7; j++) {
    if (arr[j])
    {
      digitalWrite(sda, 1);
      delayMicroseconds(2);
      digitalWrite(scl, 0);
      delayMicroseconds(2);
      digitalWrite(scl, 1);
      delayMicroseconds(2);
      digitalWrite(scl, 0);
      delayMicroseconds(2);
      digitalWrite(sda, 0);
    } else {
      delayMicroseconds(2);
      digitalWrite(sda, 0);
      delayMicroseconds(2);
      digitalWrite(scl, 0);
      delayMicroseconds(2);
      digitalWrite(scl, 1);
      delayMicroseconds(2);
      digitalWrite(scl, 0);
      delayMicroseconds(2);
      digitalWrite(sda, 0);
    }
    pinMode(sda, OUTPUT);
  }
}
uint8_t num[20] = {
  //0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f,
  0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef
};
void setup() {
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  Wire_begin();
  //delay(2000);
  //Serial_println_s("open the windows");
  Wire_beginTransmission(0x68);
    Wire_write(0x00);
    int vall = 50;
    int d = (vall/10*16) + (vall%10);
    Wire_write(d);
    Wire_endTransmission();
}
void loop() {
  Wire_beginTransmission(0x68);
  Wire_write(0x00);
  Wire_endTransmission();
  Wire_requestFrom(0x68, 6);
  char ss = Wire_read();
  char mm = Wire_read();
  char hh = Wire_read();
  char zz = Wire_read();
  char dd = Wire_read();
  char mo = Wire_read();
  int ss1 = (ss / 16);
  int ss2 = (ss % 16);
  int mouth1 = (mo / 16);
  int mouth2 = (mo % 16);
  int data1 = (dd / 16);
  int data2 = (dd % 16);
  int hour1 = (hh / 16);
  int hour2 = (hh % 16 );
  int minute1 = (mm / 16 );
  int minute2 = (mm % 16);
  i2c_start();
  i2c_Write(0x40);
  i2c_stop();
  i2c_start();
  i2c_Write(0xc0);
  i2c_Write(num[hour1]);
  i2c_Write(num[hour2]);
  i2c_Write(0x24);
  i2c_Write(num[minute1]);
  i2c_Write(num[minute2]);
  i2c_Write(0x24);
  i2c_Write(num[ss1]);
  i2c_Write(num[ss2]);
  i2c_Write(num[mouth1]);
  i2c_Write(num[mouth2]);
  i2c_Write(num[data1]);
  i2c_Write(num[data2]);
  i2c_stop();
  i2c_start();
  i2c_Write(0x8f);
  i2c_stop();
  delay(500);
  i2c_start();
  i2c_Write(0x44);
  i2c_stop();
  i2c_start();
  i2c_Write(0xc2);
  i2c_Write(0);
  i2c_Write(num[minute1]);
  i2c_Write(num[minute2]);
  i2c_Write(0);
  i2c_stop();
  i2c_start();
  i2c_Write(0x8f);
  i2c_stop();
  delay(500);
}
