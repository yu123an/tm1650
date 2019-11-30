int scl = 4;
int sda = 5;
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
    Serial.println("wite the call back");
    v = digitalRead(sda);
  }
  Serial.println("Got the call back");
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
  // for ( int j = 7; j >= 0; j--) {
  for ( int j = 0; j <= 7; j++) {
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


void setup() {
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  Serial.begin(115200);
  delay(2000);
  //Serial_println_s("open the windows");
}
void loop() {
  i2c_start();
  i2c_Write(0x44);
  i2c_stop();
  i2c_start();
  i2c_Write(0xc0);
  i2c_Write(0xbf);
  i2c_stop();
  i2c_start();
  i2c_Write(0x8f);
  i2c_stop();
  delay(20);

  delay(2000);
}
