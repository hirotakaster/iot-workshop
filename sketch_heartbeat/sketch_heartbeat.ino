void setup() {
  Serial.begin(9600);
}

void loop() {
  int res = analogRead(0);
  Serial.println(res);
  delay(20);
}
