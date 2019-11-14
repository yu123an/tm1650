#include <Wire.h>
void setup() {
  Wire_begin();
}

void loop() {
  //for( int i = 1;i<= 100;i++){
  int a = random_minmax(52,56);
  int b = random_minmax(0,255);
 Wire_beginTransmission(0x24);
 Wire_write(0x11);
 while(Wire_endTransmission() != 0){
  delay(5);
 }
 Wire_beginTransmission(a);
 Wire_write(b);
 while(Wire_endTransmission() != 0){
  delay(5);
 }
 delay(400);
//  }
}
