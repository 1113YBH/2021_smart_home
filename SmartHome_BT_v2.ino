// ▣ last update 2020.01.02 , ksyun@KNUE , GNU

#include "parameter.h"

void setup() {
  BTSerial.begin(9600);                         // 블루투스와 아두이노의 통신속도를 9600으로 설정
  BTSerial.setTimeout(200);                     // 직렬 데이터를 기다리는 최대 밀리 초를 설정
  
  pinMode(fanPin,  OUTPUT);
  pinMode(lampPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myServo.attach(servoPin);                     // 서보 연결
  servoMove(DOOR_CLOSE);  delay(500);           // 시작 시 문 닫기
  dht.begin();                                  // 온습도 측정 시작
  SPI.begin();                                  // SPI 시작
  rfid.PCD_Init();                              // RFID 모듈 시작
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;) digitalWrite(buzzPin, HIGH);        // 무한 루프
  }
  display.clearDisplay();                       // OLED 화면 지우기
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  beep(3);
  sendToApp(String("*E") + "Hello, SmartHome!" + "*");  // 사용자 화면에 시스템 시작 메시지 표시
}

void loop() {
  //(1) 입력========================================================================================
  // 센서값 읽기(조도, 거리, 온도, 습도) 
  if (isTimeToReadDHT()) getDHT();  // 온도,습도 읽기 (2초 간격으로)
  cdsValue = analogRead(cdsPin);    // 조도 읽기
  distance = getDistance();         // 거리 읽기
  getRfid();                        // RFid 카드 읽기

  // 명령어 수신  
  if (BTSerial.available()){
    beep(2);
    inString = BTSerial.readString();
  }

  //(2) 처리=========================================================================================
  cmdProcess();

  //(3) 제어=========================================================================================
  lampCtrl(lampMode);           // 전등 제어(0:켜기, 1:끄기, 2:자동제어)
  fanCtrl(fanMode);             // 팬 제어 (0:켜기, 1:끄기, 2:자동제어)
  servoCtrl(doorMode);          // 도어 제어(0:닫기, 1:열기, 2:경비, 3:차고)

  //(4) 화면 업데이트   ===============================================================================
  updateOled();                 // 시스템 화면(OLED) 업데이트
  if (isValueChanged) {
    updateAppState();           // 사용자 앱의 현재상태 업데이트
    isValueChanged = false;     
  }
  updateAppData();              // 사용자 앱의 센서값(조도,거리,온도,습도) 업데이트
  //delay(100);

}
