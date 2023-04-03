// 부저와 LED 1초 간격으로 동작
void buzzer(){
  digitalWrite(buzzPin, HIGH);
  delay(1000);
  digitalWrite(buzzPin, LOW);
  delay(1000);
}

// 비프음 n회 발생
void beep(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(buzzPin, HIGH);      // 비프 울림
    delay(20);
    digitalWrite(buzzPin, LOW);       // 비프 꺼짐
    if(n>1) delay(30);
  }
}
