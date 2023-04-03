// 초음파 센서 거리 읽기
long getDistance() {
  digitalWrite(trigPin, LOW);              // trigPin에 LOW를 출력하고
  delayMicroseconds(2);                    // 2 마이크로초가 지나면
  digitalWrite(trigPin, HIGH);             // trigPin에 HIGH를 출력합니다.
  delayMicroseconds(10);                   // trigPin을 10마이크로초 동안 기다렸다가
  digitalWrite(trigPin, LOW);              // trigPin에 LOW를 출력합니다.
  duration = pulseIn(echoPin, HIGH);       // echoPin핀에서 펄스값을 받아옵니다.
  return duration * 17 / 1000;             // d(cm) = duration(s) / 2(왕복) * 340m/s  / 100(cm로 환산)
}
