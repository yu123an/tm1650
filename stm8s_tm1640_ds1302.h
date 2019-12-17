#define _ioPin PB5
#define _clkPin PB4
#define _cePin PD3
#define THREEWIRE_READFLAG 0x01

#include <stm8s_iwdg.h>
int scl = 1;    //PA1
int sda = 0;    //PA2
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
static uint8_t bcd2bin (uint8_t val) {
  return val - 6 * (val >> 4);
}
static uint8_t bin2bcd (uint8_t val) {
  return val + 6 * (val / 10);
}
void _write(uint8_t value, bool isDataRequestCommand) {
  isDataRequestCommand = false ;
  for (uint8_t bit = 0; bit < 8; bit++) {
    digitalWrite(_ioPin, value & 0x01);
    delayMicroseconds(1);
    digitalWrite(_clkPin, HIGH);
    delayMicroseconds(1);
    if (bit == 7 && isDataRequestCommand) {
      pinMode(_ioPin, INPUT);
    }
    digitalWrite(_clkPin, LOW);
    delayMicroseconds(1);
    value >>= 1;
  }
}
void _wire_beginTransmission(uint8_t command) {
  digitalWrite(_cePin, LOW);
  pinMode(_cePin, OUTPUT);
  digitalWrite(_clkPin, LOW);
  pinMode(_clkPin, OUTPUT);
  pinMode(_ioPin, OUTPUT);
  digitalWrite(_cePin, HIGH);
  delayMicroseconds(4);
  _write(command, (command & THREEWIRE_READFLAG) == THREEWIRE_READFLAG);
}
void _wire_endTransmission() {
  digitalWrite(_cePin, LOW);
  delayMicroseconds(4);           // tCWH = 4us
}
uint8_t _wire_read() {
  uint8_t value = 0;
  for (uint8_t bit = 0; bit < 8; bit++) {
    value |= (digitalRead(_ioPin) << bit);
    digitalWrite(_clkPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_clkPin, LOW);
    delayMicroseconds(1);
  }
  return value;
}
void setup() {
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  pinMode(_clkPin, OUTPUT);
  pinMode(_ioPin, OUTPUT);
  pinMode(_cePin, OUTPUT);
  Serial_begin(9600);
  /*
     //调整时间
    _wire_beginTransmission(0xBE);
    _write(bin2bcd(40),1);//seconds
    _write(bin2bcd(59),1);//minute
    _write(bin2bcd(1),1);//hour
  */
}
void loop() {
  _wire_beginTransmission( 0xBE | 0x01);
  uint8_t second = _wire_read() & 0x7f;
  uint8_t minute = _wire_read();
  uint8_t hour = _wire_read();
  _wire_endTransmission();
  Serial_print_s("Hour:");
  Serial_println_i(bcd2bin(hour));
  Serial_print_s("minute:");
  Serial_println_i(bcd2bin(minute));
  Serial_print_s("seconds:");
  Serial_println_i(bcd2bin(second));
   i2c_start();
    i2c_Write(0x40);
    i2c_stop();
    i2c_start();
    i2c_Write(0xc0);
    i2c_Write(num[bcd2bin(hour) / 10]);
    i2c_Write(num[bcd2bin(hour) % 10]);
    i2c_Write(num[bcd2bin(minute) / 10]);
    i2c_Write(num[bcd2bin(minute) % 10]);
    i2c_stop();
    i2c_start();
    i2c_Write(0x89);
    i2c_stop();
    delay(500);
    i2c_start();
    i2c_Write(0x40);
    i2c_stop();
    i2c_start();
    i2c_Write(0xc0);
    i2c_Write(num[bcd2bin(hour) / 10]);
    i2c_Write(num[bcd2bin(hour) % 10 + 10]);
    i2c_Write(num[bcd2bin(minute) / 10 + 10]);
    i2c_Write(num[bcd2bin(minute) % 10]);
    i2c_stop();
    i2c_start();
    i2c_Write(0x89);
    i2c_stop();
    delay(490);
}
