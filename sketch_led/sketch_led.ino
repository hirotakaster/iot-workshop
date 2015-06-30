void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);  // 点灯
  delay(1000);
  digitalWrite(13, LOW);  // 消灯
  delay(1000);
}
