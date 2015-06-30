void setup() {
  // PWM PIN : 3,5,6,9,10,11
  pinMode(6, OUTPUT);
  
  // 9600bpsでシリアルを開く
  // "ツール" -> "シリアルモニタ"で閲覧可能
  Serial.begin(9600);
}

void loop() {
  // センサーから値を取得
  int val = analogRead(0);
  
  // 平均値を使う場合はこっち
  // int val = avgread(0);

  // シリアルに出力(表示用)
  Serial.println(val);

  // LEDの強弱の値にする  
  if (val >= 90 && val <= 500) {
    analogWrite(6, map(val, 90, 500, 0, 255));
  } else {
    analogWrite(6, 0);
  }

  delay(100);
}

// 平均値を取得する時の関数
#define READ_COUNT 100
int avgread(int pin) {
  int avg = 0;
  for (int i = 0 ;i < READ_COUNT; i++) {
    avg += analogRead(pin);
  }
  return avg/READ_COUNT;
}

