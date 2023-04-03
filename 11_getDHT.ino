// DHT값 읽을 때가 되었나?
boolean isTimeToReadDHT(){   
  now =  millis();           // 현재 시각 
  if (now - prevMillis >= DHTinterval) return true;       
  else return false;
}

// DHT값 읽기
void getDHT(){
  humidity = dht.readHumidity();                    // 습도 읽기
  temperature = dht.readTemperature();              // 온도 읽기
  if (isnan(humidity) || isnan(temperature) ) {     // DHT 읽기 오류 검사
    sendToApp(String("*E") + "Failed to read from DHT sensor!  *");  // 사용자 화면의 메시지 창에 표시
    return;
  }
  prevMillis = now;                                 // 현재 시각 저장
}
