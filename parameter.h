// 라이브러리 포함
#include <DHT.h>                 // 온습도 센서
#include <Servo.h>               // 서보모터
#include <Wire.h>                // OLED용 I2C
#include <SPI.h>                 // RFID를 위한 SPI
#include <MFRC522.h>             // RFID
#include <Adafruit_GFX.h>        // OLED를 위한 Adafruit 공통
#include <Adafruit_SSD1306.h>    // OLED
#include <SoftwareSerial.h>      // Serial 통신 라이브러리

// 핀번호 매칭
#define buzzPin            4     // 부저 핀번호
#define servoPin           5     // 서보모터 핀번호
#define echoPin            6     // 초음파센서(echoPin) 핀번호
#define trigPin            7     // 초음파센서(trigPin) 핀번호
#define DHTPIN             8     // 온습도센서(DHT11) 핀번호
#define RST_PIN            9     // RFID Reset PIN
#define SS_PIN            10     // RFID SS(SDA:ChipSelect) PIN
#define OLED_RESET        -1     // OLED Reset 핀번호(-1: 아두이노 RST와 공유)    
#define cdsPin            A1     // 조도센서 핀번호
#define fanPin            A2     // 12Vdc 팬 제어 릴레이 핀번호
#define lampPin           A3     // 220Vac 전등 제어 릴레이 핀번호

#define DHTTYPE        DHT11     // DHT 모델
#define DOOR_OPEN         90     // 서보모터 열기 각도
#define DOOR_CLOSE         0     // 서보모터 닫기 각도

// RFID 카드 등록
byte nuidPICC[3][4] = {{0x43, 0x90, 0x84, 0x3E},
                       {0x69, 0x4e, 0x8b, 0x99},
                       {0x19, 0x0f, 0xd2, 0xb2}};

// 객체 인스턴스 생성
Adafruit_SSD1306 display(OLED_RESET);     // OLED 인스턴스 생성
DHT dht(DHTPIN, DHTTYPE);                 // 온습도센서 인스턴스 생성
Servo myServo;                            // 서보모터 인스턴스 생성
MFRC522 rfid(SS_PIN, RST_PIN);            // RFID 인스턴스 생성
SoftwareSerial BTSerial(2, 3);            // BTSerial(Rx, Tx): Adu-Rx(2)<->BT(Tx), Adu-Tx(3)<->BT(Rx) 연결

// 시간 변수
unsigned long now = 0;                    // 현재 시각
unsigned long prevMillis = 0;             // 온습도 이전 측정 시각
const long DHTinterval = 2000;            // 온습도 측정 간격

// 모드 변수
int lampMode = 0;                         // 전등 모드(0:꺼짐, 1:켜짐, 2:조도연동 자동제어)
int fanMode = 0;                          // 팬  모드(0:꺼짐, 1:켜짐, 2:온도연동 자동제어)
int doorMode = 0;                         // 출입 모드(0:닫힘, 1:열림, 2:경비, 3:차고)

// 센서값 변수
int cdsValue = 0;                         // 조도(cds) 값
long duration, distance;                  // 초음파센서 값
float temperature = 0.;                   // 온도(dht) 값
float humidity = 0.;                      // 습도(dht) 값

// 문턱값 변수
int brightThreshold = 200;                // 조도 문턱값(threshold)
int temperThreshold = 27;                 // 온도 문턱값(threshold)
int distanceThreshold = 10;               // 거리 문턱값(threshold)

// 수신 명령어 변수
String inString = "";                     // 수신 명령

// 시스템 상황 점검 플래그
bool isValueChanged = true;               // 값이 바뀌었는가?
bool isLampOn = false;                    // 전등이 켜졌는가?
bool isFanOn = false;                     // 팬이 돌아가는가?
bool isDoorOpen = false;                  // 문이 열렸는가?


// 도어상태: 닫힘(0), 열림(1), 경비(2), 차고(3)
const char *DoorState[] = {"Closed", "Opened", "Armed", "Garage"};
