#define PIN_RGB_LED_RED 5  // 핀 번호 - RGB LED - 빨강
#define PIN_RGB_LED_GREEN 6  // 핀 번호 - RGB LED - 초록
#define PIN_RGB_LED_BLUE 7  // 핀 번호 - RGB LED - 파랑
 
void setup(){  // 최초에 1번만 실행
  // RGB LED 세팅
  pinMode(PIN_RGB_LED_RED, OUTPUT);
  pinMode(PIN_RGB_LED_GREEN, OUTPUT);
  pinMode(PIN_RGB_LED_BLUE, OUTPUT);
}
 
void loop(){  // 무한 반복 실행
  // 1초 동안 LED 색을 빨강색으로 변경
  analogWrite(PIN_RGB_LED_RED, 255);
  analogWrite(PIN_RGB_LED_GREEN, 0);
  analogWrite(PIN_RGB_LED_BLUE, 0);
  delay(1000);

  // 1초 동안 LED 색을 노랑색으로 변경
  analogWrite(PIN_RGB_LED_RED, 255);
  analogWrite(PIN_RGB_LED_GREEN, 255);
  analogWrite(PIN_RGB_LED_BLUE, 0);
  delay(1000);

  // 1초 동안 LED 색을 초록색으로 변경
  analogWrite(PIN_RGB_LED_RED, 0);
  analogWrite(PIN_RGB_LED_GREEN, 255);
  analogWrite(PIN_RGB_LED_BLUE, 0);
  delay(1000);

  // 1초 동안 LED 색을 파랑색으로 변경
  analogWrite(PIN_RGB_LED_RED, 0);
  analogWrite(PIN_RGB_LED_GREEN, 0);
  analogWrite(PIN_RGB_LED_BLUE, 255);
  delay(1000);

  // 1초 동안 LED를 끔
  analogWrite(PIN_RGB_LED_RED, 0);
  analogWrite(PIN_RGB_LED_GREEN, 0);
  analogWrite(PIN_RGB_LED_BLUE, 0);
  delay(1000);
}

