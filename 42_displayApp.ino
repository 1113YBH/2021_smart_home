// 시스템의 상태를 사용자 앱으로 전송
void updateAppState() {
  // 시스템 상태 업데이트
  String str = "";
  str = String("*S") + "Door:" + String(DoorState[doorMode]) + "\n";
  str += String(" > L(") + lampMode + "):" + isLampOn + "\n";
  str += String(" > F(") + fanMode + "):" + isFanOn + "\n";
  str += String(" > D(") + doorMode + "):" + isDoorOpen + "\n*";
  BTSerial.println(str);
  delay(50);

  // 전등(L) 환풍(F) 도어(D) 표시 업데이트
  if (isLampOn) str = "*LR255G0B0 "; //전등
  else str = "*LR80G0B0 ";
  if (isFanOn) str += "*FR0G255B0 "; //환풍
  else str += "*FR0G80B0 ";
  if (isDoorOpen) str += "*DR0G0B255 *";//출입
  else str += "*DR0G0B80 *";
  BTSerial.println(str);
  delay(10);

  // 전등(L) 환풍(F) 도어(D) thereshold값 업데이트
  str = "*b" + String(brightThreshold) + "*t" + String(temperThreshold) + "*u" + String(distanceThreshold) + "*";
  BTSerial.println(str);
  //Serial.println(str); //*******************************************
  delay(10);
}

// 읽은 센서값을 사용자 앱으로 전송(조도,거리,온도,습도)
void updateAppData() {
  if (!myServo.attached()){
    sendToApp(String("*B") + String(cdsValue) + "*U" + String(distance) + "*");
    sendToApp(String("*T") + String(temperature, 1) + "*H" + String(humidity, 1) + "*");
  }
}

// 사용자 앱으로 데이터 전송
void sendToApp(String msg) {
  BTSerial.println(msg);
  delay(10);
}
