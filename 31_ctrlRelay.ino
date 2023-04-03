
// 전등 제어
void lampCtrl(int lampMode){
  if (lampMode == 0 || lampMode == 1) {       // 전등 끄기, 켜기
    digitalWrite(lampPin, !lampMode);         // Active Low(Low일 때 켜짐)
    isLampOn = lampMode;
  }
  if (lampMode == 2) lampAutoCtrl();          // 전등 자동 제어(조도에 따라 켜고 끔)
}

// 전등 자동 제어
void lampAutoCtrl(){
    if (cdsValue > brightThreshold && !isLampOn) {        //어두운데 전등이 꺼져있으면
      digitalWrite(lampPin, LOW);
      isLampOn = true;                                        //전등 켜기(Active Low)
      isValueChanged = true;
    } else if (cdsValue < brightThreshold && isLampOn) {  //밝은데 불이 켜져있으면
      digitalWrite(lampPin, HIGH);
      isLampOn = false;                                       //전등 끄기(Active Low)
      isValueChanged = true;
    }
}


// 팬 제어
void fanCtrl(int fanMode){
  if (fanMode == 0 || fanMode == 1) {       // 팬 끄기, 켜기
    digitalWrite(fanPin, !fanMode);         // Active Low(Low일 때 켜짐)
    isFanOn = fanMode;
  }
  if (fanMode == 2) fanAutoCtrl();          // 팬 자동 제어(온도에 따라 켜고 끔)
}

// 팬 자동 제어 모드
void fanAutoCtrl(){
    if (temperature > temperThreshold && !isFanOn) {       // 온도가 설정치보다 높고 팬이 꺼져있으면
      digitalWrite(fanPin, LOW);
      isFanOn = true;                                         // 팬 켜기(Active Low)
      isValueChanged = true;
    } else if (temperature < temperThreshold && isFanOn) { // 온도가 설정치보다 낮고 팬이 켜져있으면
      digitalWrite(fanPin, HIGH);
      isFanOn = false;                                        // 팬 끄기(Active Low)
      isValueChanged = true;
    }
}
