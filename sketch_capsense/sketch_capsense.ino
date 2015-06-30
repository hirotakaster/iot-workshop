#include <CapacitiveSensor.h>
CapacitiveSensor  capsensor = CapacitiveSensor(4,2);

void setup() {
  // 読取りタイムアウトの設定
  capsensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
  
  // 9600bpsでシリアルを開く
  // "ツール" -> "シリアルモニタ"で閲覧可能
  Serial.begin(9600);
}

void loop() {
  // 30回のサンプル値を取得
  long val =  capsensor.capacitiveSensor(30);
  
  // シリアルに出力(表示用)
  Serial.println(val);

  // LEDのON/OFFの値にする 
  if (val >= 1000) {
    analogWrite(6, 255);
  } else {
    analogWrite(6, 0);
  }
  delay(100);
}

