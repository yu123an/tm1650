
#define _ioPin PB5
#define _clkPin PB4
#define _cePin PD3
#define THREEWIRE_READFLAG 0x01
#define  scl PA2
#define  sda PA1
#define  led PD2
/****************************************************************/
/*----------------------TM640驱动-------------------------------*/
/***************************************************************/
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
/****************************************************************/
/*-----------------------字符集---------------------------------*/
/***************************************************************/
uint8_t num[20] = {
  //0x00  0x01  0x02  0x03  0x04  0x05  0x06  0x07  0x08  0x09
  0x3F, 0x30, 0x5B, 0x79, 0x74, 0x6d, 0x6f, 0x38, 0x7f, 0x7d,
  0xbf, 0xb0, 0xdb, 0xf9, 0xf4, 0xed, 0xef, 0xb8, 0xff, 0xfd
};
/****************************************************************/
/*-----------------------亮度值---------------------------------*/
/***************************************************************/
uint8_t comm[8] = {
  0x8f, 0x8e, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88
};
/****************************************************************/
/*-----------------------进制转换--------------------------------*/
/***************************************************************/
static uint8_t bcd2bin (uint8_t val) {
  return val - 6 * (val >> 4);
}
static uint8_t bin2bcd (uint8_t val) {
  return val + 6 * (val / 10);
}
/****************************************************************/
/*-----------------------ds1302驱动--------------------------------*/
/***************************************************************/
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
  pinMode(led, OUTPUT);
  pinMode(_clkPin, OUTPUT);
  pinMode(_ioPin, OUTPUT);
  pinMode(_cePin, OUTPUT);
//  Serial_begin(9600);
  //调整时间,每天凌晨定时重启，设置时间
  _wire_beginTransmission(0xBE);
  _write(bin2bcd(2), 1); //seconds
  _write(bin2bcd(16), 1); //minute
  _write(bin2bcd(1), 1); //hour
}
void loop() {
  /****************************************************************/
  /*-----------------------获取当下时间-----------------------------*/
  /***************************************************************/
  _wire_beginTransmission( 0xBE | 0x01);
  uint8_t second = _wire_read() & 0x7f;
  uint8_t minute = _wire_read();
  uint8_t hour = _wire_read();
  _wire_endTransmission();
  //Serial_print_s("Hour:");
 // Serial_println_i(bcd2bin(hour));
 // Serial_print_s("minute:");
 // Serial_println_i(bcd2bin(minute));
 // Serial_print_s("seconds:");
 // Serial_println_i(bcd2bin(second));
  /****************************************************************/
  /*-----------------------tm1640显示时间--------------------------*/
  /***************************************************************/
  i2c_start();
  i2c_Write(0x40);
  i2c_stop();
  i2c_start();
  i2c_Write(0xc0);
  i2c_Write(num[bcd2bin(second) % 10]);
  i2c_Write(num[bcd2bin(second) / 10]);
  i2c_Write(num[bcd2bin(minute) % 10]);
  i2c_Write(num[bcd2bin(minute) / 10]);
  i2c_Write(num[bcd2bin(hour) % 10]);
  i2c_Write(num[bcd2bin(hour) / 10]);
  i2c_stop();
  i2c_start();
  i2c_Write(0x8f);
  i2c_stop();
  digitalWrite(led, 1);
  delay(499);
  digitalWrite(led, 0);
  delay(500);
}
