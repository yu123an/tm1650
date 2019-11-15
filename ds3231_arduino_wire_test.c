#include <Wire.h>
uint8_t num[3] = { 0x68, 0xd0, 0xd1 };
void setup() {
  Serial_begin(9600);
  Wire_begin();
}
void loop() {
  for (int i = 2; i < 3; i++) {
  for (int j = 2; j < 3; j++) {
    Wire_beginTransmission(num[i]);
      Wire_write(0x00);
      while (Wire_endTransmission() == 0) {
        Serial_println_s("writting the cking");
        delay(50);
      }
      Wire_requestFrom(num[j], 1);
      while (Wire_available() == 0) {
        Serial_println_s("Recvile......");
        Serial_println_i(num[i]);
        Serial_println_i(num[j]);
        delay(50);
      }
      int a = Wire_read();
      Serial_println_i(a);
      Serial_println_s("+----------------+");
      delay(2000);
    }
  }
}
