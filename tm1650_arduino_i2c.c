#include <I2C.h>
void setup() {
 // Serial_begin(9600);
  I2C_begin();
}
void loop() {
  for( int t = 0;t<= 255; t++){
  I2C_begin();
  I2C_write(0x24, 0x11);
  I2C_end();
  I2C_begin();
  I2C_write(0x36, t);
  I2C_end();
  
  delay(2000);
  }
}
