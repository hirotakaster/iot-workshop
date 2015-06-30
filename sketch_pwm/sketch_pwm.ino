void setup() {
  // PWM PIN : 3,5,6,9,10,11
  pinMode(6, OUTPUT);
}

void loop() {
  // PWMは0-255まで
  
  // ゆっくり明るくなる
  for (int i = 0; i <= 255; i++) {
    analogWrite(6, i);
    delay(20);
  }
  
  // ゆっくり暗くなる
  for (int i = 255; i >= 0; i--) {
    analogWrite(6, i);
    delay(20);
  }
}
