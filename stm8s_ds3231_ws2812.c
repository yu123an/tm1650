#include<SPI.h>
#include<Wire.h>
static uint8_t bcd2bin (uint8_t val) {
  return val - 6 * (val >> 4);
}
static uint8_t bin2bcd (uint8_t val) {
  return val + 6 * (val / 10);
}
uint8_t number[10] = {B00111111, B00100001, B01110110, B01110011, B01101001, B01011011, B01011111, B00110001, B01111111, B01111011};
void write_byte(uint8_t num) {
  for (int i = 0; i <= 7; i++) {
    if (num & 0x80) {
      SPI_transfer(0x7c);
    } else {
      SPI_transfer(0x70);
    }
    num <<= 1;
  }
}
void write_led(uint8_t numa, uint8_t numb, uint8_t numc) {
  write_byte(numa);
  write_byte(numb);
  write_byte(numc);
}
void write_num(uint8_t data) {
  for (int i = 0; i <= 6; i++) {
    if (data << 1 & 0x80) {
      for (int j = 0; j <= 3; j++) {
        write_led(1, 0, 0);
      }
    } else {
      for (int j = 0; j <= 3; j++) {
        write_led(0, 0, 0);
      }
    }
    data <<= 1;
  }
}
void setup() {
  Wire_begin();
 // Serial_begin(9600);
  SPI_begin();
 
}
void loop() {
  Wire_beginTransmission(0x68);
  Wire_write(0x00);
  Wire_endTransmission();
  Wire_requestFrom(0x68, 3);
  int ss = Wire_read();
  int mm = Wire_read();
  int hh = Wire_read();
  int ss1 = (ss / 16);
  int ss2 = (ss % 16);
  int hour1 = (hh / 16);
  int hour2 = (hh % 16 );
  int minute1 = (mm / 16 );
  int minute2 = (mm % 16);
  
  write_num(number[hour1]);
  write_num(number[hour2]);
  write_num(number[minute1]);
  write_num(number[minute2]);
  delay(500);
   write_num(number[hour1]);
  write_num(number[hour2]);
  write_num(number[ss1]);
  write_num(number[ss2]);
  delay(490);
}
