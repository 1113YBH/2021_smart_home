// 수신한 명령어를 파싱하고 해석
// 명령 프로토콜 :  Lx(전등), Fx(환풍), Dx(출입), Uxx(거리-문턱값), Txx(온도-문턱값), Bxx(조도-문턱값)
//                 x값 :  0-끄기, 1-켜기, 2-자동 혹은 경비, 3-차고(출입만 해당), 문턱값

void cmdProcess() {
  // 명령어 parsing
  String inNumber = inString.substring(1, inString.length());     // 제어값 x만 취함
  int inValue = inNumber.toInt();                                 // 제어값 x를 정수로 변환

  // 명령어 해석
  switch (inString[0]) {
    case 'L':                       // 전등 제어 명령
      lampMode = inValue;
      break;
    case 'F':                       // 팬 제어 명령
      fanMode = inValue;
      break;
    case 'D':                       // 도어 제어 명령
      doorMode = inValue;
      break;
    case 'U':                       // 초음파센서 threshold 설정
      distanceThreshold = inValue;
      break;
    case 'T':                       // 온도연동 threshold 설정
      temperThreshold = inValue;
      break;
    case 'B':                       // 조도연동 threshold 설정
      brightThreshold = inValue;
      break;
  }
  sendToApp(String("*E") + "Rx Cmd > " + inString + "*");  // 사용자 화면에 시스템 시작 메시지 표시
  isValueChanged = true;              //사용자 화면 업데이트 플래그
}
