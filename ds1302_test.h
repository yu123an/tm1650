#define scl PB4
#define sda PB5
#define ce  PD3
void down() {
  digitalWrite(scl, 1);
  delayMicroseconds(1);
  digitalWrite(scl, 0);
  delayMicroseconds(1);
}

void write_byte(uint8_t bytes) {
  uint8_t t = 0x01;
  for (int i = 0; i <= 7; i++) {
    digitalWrite(sda,(bytes & t));
                 t <<= 1;
                 down();
  }
  digitalWrite(sda, 1);
}

void write_data(uint8_t add, uint8_t num) {
  digitalWrite(ce, 0);
  digitalWrite(scl, 0);
  digitalWrite(ce, 1);
  write_byte((add << 1) | 0x80);
  write_byte(num);
  digitalWrite(ce, 0);
}
uint8_t read_byte() {
  pinMode(sda, INPUT);
  uint8_t data;
  uint8_t t = 0x01;
  for (int i = 0; i < 7; i++) {
    if (digitalRead(sda)) {
      data = data | t;
    }
    t <<= 1;
    down();
  }
  return data;
  pinMode(sda, OUTPUT);
}
uint8_t read_data(uint8_t add) {
  uint8_t data = 0;
  digitalWrite(ce, 0);
  digitalWrite(scl, 0);
  digitalWrite(ce, 1);
  write_byte((add << 1) | 0x81);
  data = read_byte();
  digitalWrite(ce, 0);
  digitalWrite(scl, 1);
  digitalWrite(sda, 1);
  digitalWrite(sda, 0);
  return data;
}
void setup() {
  pinMode(scl, OUTPUT);
  pinMode(sda, OUTPUT);
  pinMode(ce , OUTPUT);
  Serial_begin(9600);
}
void loop() {
  int timer = read_data(0x01);
  Serial_println_i(timer);
  delay(1000);
}
