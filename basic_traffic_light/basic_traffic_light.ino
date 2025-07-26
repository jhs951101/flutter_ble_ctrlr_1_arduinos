#define PIN_LED_RED 2  // 빨강색 LED 핀 번호
#define PIN_LED_YELLOW 3  // 노랑색 LED 핀 번호
#define PIN_LED_GREEN 4  // 초록색 LED 핀 번호
 
void setup(){  // 최초에 1번만 실행
  // LED 3개 모두 설정
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
}
 
void loop(){  // 무한 반복 실행
  // 3초 동안 초록색 LED만 킴
  digitalWrite(PIN_LED_GREEN, HIGH);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_RED, LOW);
  delay(3000);  // 3초 지연 [ 단위: 밀리세컨드(ms), 1초 = 1000ms ]

  // 1초 동안 노랑색 LED만 킴
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, HIGH);
  digitalWrite(PIN_LED_RED, LOW);
  delay(1000);

  // 2초 동안 빨강색 LED만 킴
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_LED_RED, HIGH);
  delay(2000);
}

