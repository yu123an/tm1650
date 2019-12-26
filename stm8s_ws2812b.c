#include<SPI.h>
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
    if (data<<1 & 0x80) {
      for (int j = 0; j <= 3; j++) {
        write_led(0, 0, 1);
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
  SPI_begin();
}
void loop() {
  write_num(2);
  delay(2000);
}
