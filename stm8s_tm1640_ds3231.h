#include <Wire.h>
#include <stm8s_iwdg.h>
int scl = 0;    //PA1
int sda = 1;    //PA2
#define led 6
//i2c drive
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
  for (int i = 0; i <= 7; i++) {
    if (data % 2) {
      digitalWrite(sda, 1);
      delayMicroseconds(2);
      digitalWrite(scl, 0);
      delayMicroseconds(2);
      digitalWrite(scl, 1);
      delayMicroseconds(2);
      digitalWrite(scl, 0);
      delayMicroseconds(2);
      digitalWrite(sda, 0);
    }
    else
    {
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
    data /= 2;
  }
}
// define the number
uint8_t num[20] = {
  //0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f,
  0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef
};
uint8_t comm[8] = {
  0x8f,0x8e,0x8d,0x8c,0x8b,0x8a,0x89,0x88
};
void setup() {
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  Wire_begin();
}
void loop() {
  int light = (analogRead(led) / 25);
  //get the time
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
  int day = (hh % 16);
  int mouth1 = (mo / 16);
  int mouth2 = (mo % 16);
  int data1 = (dd / 16);
  int data2 = (dd % 16);
  int hour1 = (hh / 16);
  int hour2 = (hh % 16 );
  int sss = ((ss1 * 10) + ss2);
  int minute1 = (mm / 16 );
  int minute2 = (mm % 16);
  if (sss == 0) {
    for (int j = 0; j <= 9; j++) {
      i2c_start();
      i2c_Write(0x44);
      i2c_stop();
      i2c_start();
      i2c_Write(0xc0);
      for (int i = 1; i <= 12; i++) {
        int a = random_minmax(0, 19);
        i2c_Write(num[a]);
      }
      i2c_stop();
      i2c_start();
      i2c_Write(comm[light]);
      i2c_stop();
      delay(80);
    }
  } else {
    i2c_start();
    i2c_Write(0x40);
    i2c_stop();
    i2c_start();
    i2c_Write(0xc0);
    i2c_Write(num[hour1]);
    i2c_Write(num[hour2]);
    i2c_Write(num[minute1]);
    i2c_Write(num[minute2]);
    i2c_Write(num[ss1]);
    i2c_Write(num[ss2]);
    i2c_Write(64);
    i2c_Write(num[mouth1]);
    i2c_Write(num[mouth2]);
    i2c_Write(num[data1]);
    i2c_Write(num[data2]);
    i2c_Write(64);
    i2c_stop();
    i2c_start();
    i2c_Write(comm[light]);
    i2c_stop();
    delay(500);
    for (int j = 0; j <= 9; j++) {
      i2c_start();
      i2c_Write(0x44);
      i2c_stop();
      i2c_start();
      i2c_Write(0xc2);
      i2c_Write(num[minute1 + 10]);
      i2c_Write(num[minute2 + 10]);
      i2c_Write(num[ss1]);
      i2c_Write(num[ss2]);
      i2c_Write(64);
      for (int i = 1; i <= 4; i++) {
        int a = random_minmax(0, 19);
        i2c_Write(num[a]);
      }
      i2c_stop();
      i2c_start();
     i2c_Write(comm[light]);
      i2c_stop();
      delay(40);
    }
  }
}
