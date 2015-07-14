// 基本パラメータ
float offset = 0.424;         //offset 424mv（0℃の時424mVを出力）
float vc = 0.00625;           // +6.25mv/℃
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  int sensorValue = analogRead(0);
  
  // 5Vの時の参照値
  float v = float(sensorValue) / 1024 * 5.0;
  float temp = (v - offset) / vc;
  Serial.println(temp);
  delay(1000);
}
