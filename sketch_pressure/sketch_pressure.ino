void setup() {
  // PWM PIN : 3,5,6,9,10,11
  pinMode(6, OUTPUT);
  
  // 9600bpsでシリアルを開く
  // "ツール" -> "シリアルモニタ"で閲覧可能
  Serial.begin(9600);
}

void loop() {
  // センサーから値を取得して重さを測定
  float val = calweight(analogRead(0));

  // 平均値を使う場合はこっち
  // float val = calweight(avgread(0));

  // シリアルに出力(表示用)
  Serial.println(val);

  // LEDの強弱の値にする 
  if (val >= 500 && val <= 5000) {
    analogWrite(6, map(val, 0, 5000, 0, 255));
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

// 重さを測定する関数
// R1は抵抗10Ω
float R1 = 10.0;
float calweight(float data){
    return 880.79/(R1 * data/(1024.0 - data)) - 0.05;    
}

