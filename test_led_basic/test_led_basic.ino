#define PIN_BASIC_LED_RED 2  // 핀 번호 - 빨강색 기본 LED
#define PIN_BASIC_LED_GREEN 3  // 핀 번호 - 초록색 기본 LED

void setup(){  // 최초에 1번만 실행
  // LED 2개 모두 설정
  pinMode(PIN_BASIC_LED_RED, OUTPUT);
  pinMode(PIN_BASIC_LED_GREEN, OUTPUT);
}
 
void loop(){  // 무한 반복 실행
  // 2초 동안 초록색 LED만 킴
  digitalWrite(PIN_BASIC_LED_GREEN, HIGH);
  digitalWrite(PIN_BASIC_LED_RED, LOW);
  delay(2000);  // 2초 지연 [ 단위: 밀리세컨드(ms), 1초 = 1000ms ]

  // 1초 동안 빨강색 LED만 킴
  digitalWrite(PIN_BASIC_LED_GREEN, LOW);
  digitalWrite(PIN_BASIC_LED_RED, HIGH);
  delay(1000);
}