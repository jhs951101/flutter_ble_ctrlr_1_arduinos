#define PIN_SERVO 8  // 핀 번호 - 서보 모터
 
Servo mini_servo;

void setup(){  // 최초에 1번만 실행
  // 서보 모터 세팅
  mini_servo.attach(PIN_SERVO);
}
 
void loop(){  // 무한 반복 실행
    // 서보 모터의 회전 각도를 0도로 변경
    mini_servo.write(0);
    delay(1000);

    // 서보 모터의 회전 각도를 20도로 변경
    mini_servo.write(20);
    delay(1000);

    mini_servo.write(40);
    delay(1000);

    mini_servo.write(60);
    delay(1000);
}

