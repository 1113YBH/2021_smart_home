//RFID 읽기
void getRfid() {
  bool isAuthID;

  if ( ! rfid.PICC_IsNewCardPresent()) return; //새 카드가 인식되지 않았다면 더이상 진행하지 말고 빠져나감
  if ( ! rfid.PICC_ReadCardSerial()) return;   //ID가 인식되지 않았다면 더이상 진행하지 말고 빠져나감
  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);  //PICC 타입 읽어오기
  //Serial.println(rfid.PICC_GetTypeName(piccType));

  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    BTSerial.println(String("*E") + "Your tag is not of type MIFARE Classic.\n" + "*");
    delay(10);
    return;   //MIFARE 방식이 아니라면 더이상 진행하지 말고 빠져나감
  }

  // 등록된 카드(ID)인지 확인
  for (int i = 0; i < sizeof(nuidPICC) / sizeof(nuidPICC[0]); i++) {
    isAuthID = true;                                // true로 시작하여
    for (int j = 0; j < 4; j++) {                   // 한자리씩 비교
      if (rfid.uid.uidByte[j] !=  nuidPICC[i][j]) { // 등록된 카드와 맞지 않으면
        isAuthID = false;                           // false로 설정하고
        break;                                      // 안쪽 for문을 빠져나감
      }
    }
    if (isAuthID) break;                            // 네자리 모두 같으면 등록된 카드이므로 바깥쪽 for문을 나감
  }

  if (isAuthID) {  // 등록된 카드인 경우
    BTSerial.println(String("*E") + "This is a confirmed Card.\n" + "*");
    digitalWrite(buzzPin, LOW);      // 경보 해제
    rfidServoCtrl();                 // 도어 제어
  }
  else {
    //등록된 ID가 아니라면 사용자 화면에 tag 정보 표시
    printHex(rfid.uid.uidByte, rfid.uid.size); // 사용자 화면에 부정 tag 정보 출력
    digitalWrite(buzzPin, HIGH);               // 경보 울림
  }

  //rfid 종료
  rfid.PICC_HaltA();      // PICC 종료
  rfid.PCD_StopCrypto1(); // 암호화 종료

  isValueChanged = true;
}

//16진수 표시
void printHex(byte * buffer, byte bufferSize) {
  String str = "";
  for (byte i = 0; i < bufferSize; i++) {
    str += (buffer[i] < 0x10 ? " 0" : " ");
    str += String(buffer[i], HEX);
  }
  BTSerial.println(String("*E") + "Unconfirmed Card [" + str + "]\n*");
}

// RFID 재시작
void rfidRestart() {
  SPI.end();
  SPI.begin();                // SPI 시작
  rfid.PCD_Init();            // RFID 모듈 시작
}
