#include <Wire.h>
int scl = 1;    //PA1
int sda = 0;    //PA2
int led = PC4 ;
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
  0x8f, 0x8e, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88
};
void setup() {

  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  Serial_begin(9600);
  // Wire_begin();
}
void loop() {
  // int light = (analogRead(led) / 25);
  int minute;
  int hour;
  int minute1;
  int minute2;
  int hour1;
  int hour2;
  for (int time = 3600; time >= 0; time--) {
   // Serial_println_i(light);
    hour = time / 60;
    minute = time % 60;
    hour1 = hour / 10;
    hour2 = hour % 10;
    minute1 = minute / 10;
    minute2 = minute % 10;
    i2c_start();
    i2c_Write(0x40);
    i2c_stop();
    i2c_start();
    i2c_Write(0xc0);


    i2c_Write(num[hour1]);
    i2c_Write(num[hour2 + 10]);
    i2c_Write(num[minute1 + 10]);
    i2c_Write(num[minute2]);

    i2c_stop();
    i2c_start();
    i2c_Write(0x89);
    i2c_stop();

    delay(490);
    i2c_start();
    i2c_Write(0x40);
    i2c_stop();
    i2c_start();
    i2c_Write(0xc0);


    i2c_Write(num[hour1]);
    i2c_Write(num[hour2]);
    i2c_Write(num[minute1]);
    i2c_Write(num[minute2]);

    i2c_stop();
    i2c_start();
    i2c_Write(0x89);
    i2c_stop();
    delay(490);
  }
  delay(2000);
}
