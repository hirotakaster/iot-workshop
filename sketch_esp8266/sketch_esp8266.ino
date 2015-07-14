// ITEADLIB_Arduino_WeeESP8266 をLibraryに入れる
// Macの場合、
// cd ~/Documents/Arduino/libraries/
// git clone https://github.com/itead/ITEADLIB_Arduino_WeeESP8266
// Windowsの場合
// My Documents -> Arduino -> libraries に入れる
//
// ESP8266.h に ESP8266_USE_SOFTWARE_SERIAL がコメントアウトされて
// いるので、コメントアウトを除去しておくこと。
// Arduinoのメニューにある、[ファイル]->[スケッチの例]->[ITEADLIB_Arduino_WeeESP8266]に
// 色々とサンプルがあるから見てみてね。
//
// TX->RX1(2)
// RX->TX1(3)
// EN ->3.3V (5Vにすると一発で壊れちゃうので注意!!)
// VCC->3.3V
// GND->GND
// Arduinoのバッファ(64byte)が少ない場合があるので、以下のファイルを修正も可
// /arduino/hardware/arduino/avr/cores/arduino/HardwareSerial.h
// #define SERIAL_BUFFER_SIZE 64 -> 256 とか。
//
#include "ESP8266.h"
#define SSID        "hirotakaster"     // SSID
#define PASSWORD    "1234567890"       // パスワード
#include <SoftwareSerial.h>

// ソフトシリアルを利用
SoftwareSerial mySerial(2,3);
ESP8266 wifi(mySerial);

// 接続するサーバ
#define HOST_NAME   "203.189.96.80"
#define HOST_PORT   (80)


void setup(void) {
  Serial.begin(9600);
  Serial.print("setup begin\r\n");

  // WiFiに接続
  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  // WiFiに接続するモード
  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  // SSID/Passwordで接続
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");

    Serial.print("IP:");
    Serial.println( wifi.getLocalIP().c_str());       
  } else {
    Serial.print("Join AP failure\r\n");
  }

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }

  Serial.print("setup end\r\n");
}
 
void loop(void) {
  uint8_t buffer[512] = {0};

  // TCP接続する
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    Serial.print("create tcp ok\r\n");
  } else {
    Serial.print("create tcp err\r\n");
  }

  // リクエストを作成(温度センサーのデータをGET/Postしたり)
  String requestString = "GET /index.html";
  requestString.concat(" HTTP/1.1\r\nHost: 203.189.96.80\r\nConnection: close\r\n\r\n");
  char requestText[requestString.length() + 1];
  requestString.toCharArray(requestText, requestString.length() + 1);

  // 送信
  wifi.send((const uint8_t*)requestText, strlen(requestText));

  // 受信と表示
  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
    Serial.print("Received:[");
    for(uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
  }

  // TCPを解放
  if (wifi.releaseTCP()) {
    Serial.print("release tcp ok\r\n");
  } else {
    Serial.print("release tcp err\r\n");
  }
  delay(10000);    
}
     
