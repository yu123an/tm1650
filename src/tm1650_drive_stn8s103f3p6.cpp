#define scl PC6
#define sda PC7
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
void i2c_ack() {
  int v = digitalRead(sda);
  while (v == 1) {
    delay(10);
    Serial_println_s("wite the call back");
    v = digitalRead(sda);
  }
  Serial_println_s("Got the call back");
  pinMode(sda, OUTPUT);
  digitalWrite(scl, 0);
  delayMicroseconds(2);
  digitalWrite(sda, 1);
  delayMicroseconds(2);
  digitalWrite(scl, 1);
  delayMicroseconds(2);
  digitalWrite(scl, 0);
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
  for ( int j = 7; j >= 0; j--) {
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

/*
void setup() {
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  Serial_begin(115200);
  delay(2000);
  //Serial_println_s("open the windows");
}

void loop() {
  for(int p = 0;p <= 255;p++){
  for(int q = 104;q <= 110;q+=2){
  
  Serial_println_s("begin");
  i2c_start();
  i2c_Write(0x48);
  i2c_ack();
  i2c_Write(0x49);
  i2c_ack();
  i2c_stop();
  i2c_start();
  i2c_Write(q);
  i2c_ack();
  i2c_Write(p);
  i2c_ack();
  i2c_stop();
  delay(20);
  }
  }
  delay(2000);
}
*/
