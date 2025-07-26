#define PIN_DISTANCE_ECHO 10  // 핀 번호 - 거리 센서 - ECHO (INPUT)
#define PIN_DISTANCE_TRIG 11  // 핀 번호 - 거리 센서 - ECHO (OUTPUT)
 
void setup(){  // 최초에 1번만 실행
  // 시리얼 모니터 세팅
  Serial.begin(9600);
  while(!Serial);

  // 거리 센서 세팅
  pinMode(PIN_DISTANCE_TRIG, OUTPUT);
  pinMode(PIN_DISTANCE_ECHO, INPUT);
}
 
void loop(){  // 무한 반복 실행
  // 거리 측정 후 cm 단위로 출력
  long distanceCm = getDistanceCm();

  Serial.print("DIstance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  delay(1000);
}

long getDistanceCm(){  // 거리 센서에서 거리를 잰 후 cm 단위로 알려주는 함수
  long result = -1;
  digitalWrite(PIN_DISTANCE_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_DISTANCE_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_DISTANCE_TRIG, LOW);

  long duration = pulseIn(PIN_DISTANCE_ECHO, PIN_DISTANCE_TRIG);
  long distanceCm = duration * 17 / 1000;

  result = distanceCm;
  return result;
}