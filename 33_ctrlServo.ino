void servoCtrl(int doorMode) {
  if (doorMode == 0 && isDoorOpen) servoMove(DOOR_CLOSE);   // 도어 닫기
  if (doorMode == 1 && !isDoorOpen)servoMove(DOOR_OPEN);    // 도어 열기
  if (doorMode == 2) armedModeHomeGuard();                  // 경비 모드(초음파 센서에 따라 경보음 발생)
  if (doorMode == 3) garageModeServoAction();               // 차고 모드(초음파 센서에 따라 서보모터 동작)
}

//서보모터 제어
void servoMove(int servoPos) {
  isValueChanged = true;
  myServo.attach(servoPin); // 서보모터 연결
  myServo.write(servoPos);  // 움직이기
  delay(500);               // 움직임이 끝날 때까지 기다리기
  myServo.detach();         // 서보모터 분리
  if (servoPos == DOOR_OPEN) isDoorOpen = true;   //문 열기
  if (servoPos == DOOR_CLOSE) isDoorOpen = false; //문 닫기
}

// 경비모드 서보모터 제어
void armedModeHomeGuard() {
  // 경계 범위 안으로 접근하면 부저 & RGB 경보 울림
  if (distance < distanceThreshold) digitalWrite(buzzPin, HIGH);
  // 경계 범위 밖으로 벗어나면 부저 & RGB 경보 해제
  else digitalWrite(buzzPin, LOW);
}

// 차고모드 서보모터 제어
void garageModeServoAction() {
  if (distance < distanceThreshold && !isDoorOpen) { //가까이 왔는데 닫혀있으면
    if (!myServo.attached()) servoMove(DOOR_OPEN);   //차고문 열기(서보가 동작 중이 아니면)
  }
  if (distance > distanceThreshold && isDoorOpen) {  //멀어졌는데 열려있으면
    if (!myServo.attached()) servoMove(DOOR_CLOSE);  //차고문 닫기(서보가 동작 중이 아니면)
  }
}

// RFID 서보모터 제어
void rfidServoCtrl() {
  if (isDoorOpen) { //문이 열린 상태이면 문닫고 경비모드 설정
    servoMove(DOOR_CLOSE);  //문닫고
    doorMode = 2;           //경비모드 설정
    BTSerial.println(String("*E") + " Door is " + String(DoorState[doorMode]) + ".\n*");
    delay(10);
  }
  else {            //문이 닫힌 상태이면 경비모드 해제하고 문 열고 닫기(출입)
    doorMode = 0;                   //경비모드 해제 -> 문 닫기 모드
    servoMove(DOOR_OPEN);           //문 열기 후 문 닫기 모드에 의해 자동으로 닫힘
  }
}
