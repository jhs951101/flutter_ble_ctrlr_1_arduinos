#include <Servo.h>
#include <ArduinoBLE.h>

//

#define PIN_BASIC_LED_RED 2  // 핀 번호 - 빨강색 기본 LED
#define PIN_BASIC_LED_GREEN 3  // 핀 번호 - 초록색 기본 LED

#define PIN_RGB_LED_RED 5  // 핀 번호 - RGB LED - 빨강
#define PIN_RGB_LED_GREEN 6  // 핀 번호 - RGB LED - 초록
#define PIN_RGB_LED_BLUE 7  // 핀 번호 - RGB LED - 파랑

#define PIN_SERVO 8  // 핀 번호 - 서보 모터

#define PIN_DISTANCE_ECHO 10  // 핀 번호 - 거리 센서 - ECHO (INPUT)
#define PIN_DISTANCE_TRIG 11  // 핀 번호 - 거리 센서 - ECHO (OUTPUT)

//

#define LOCAL_NAME "A"  // 기기명 (BLE 연결 시 쓰임)
#define DEVICE_NAME "AD"  // 기기명

#define MAX_BYTES_BLE 20  // BLE로 데이터를 주고받을 때 1회당 최대 bytes (ex: 값이 20이면 1회당 최대 20개의 영문 or 숫자 or 특수문자를 보낼 수 있음)
#define NUM_OF_ALLOWED_CHARS 4
#define MAX_NUM_OF_PARTS_SPLIT 10

#define UUID_SERVICE "19B10000-E8F2-537E-4F6C-D104768A1212"  // 연결을 관리하기 위한 UUID 중 일부 (맨 앞, 맨 뒤, 문자 제외)
#define UUID_CHAR "19B10001-E8F2-537E-4F6C-D104768A1212"  // 문자를 주고 받기 위한 UUID 중 일부 (맨 앞, 맨 뒤, 문자 제외)

//

String operationType = "";
char allowingChars[NUM_OF_ALLOWED_CHARS] = { ' ', '_', '[', ']' };

Servo mini_servo;
BLEService customService(UUID_SERVICE);  // 연결을 관리하는 객체
BLECharacteristic customCharacteristic(UUID_CHAR, BLERead | BLEWrite | BLENotify, MAX_BYTES_BLE);  // 문자를 주고 받는 객체

//

void setup(){
  // 시리얼 모니터 세팅
  Serial.begin(9600);
  while(!Serial);
  
  // Basic LED 2개 세팅
  pinMode(PIN_BASIC_LED_RED, OUTPUT);
  pinMode(PIN_BASIC_LED_GREEN, OUTPUT);
  
  // RGB LED 세팅
  pinMode(PIN_RGB_LED_RED, OUTPUT);
  pinMode(PIN_RGB_LED_GREEN, OUTPUT);
  pinMode(PIN_RGB_LED_BLUE, OUTPUT);
  
  // 서보 모터 세팅
  mini_servo.attach(PIN_SERVO);

  // 거리 센서 세팅
  pinMode(PIN_DISTANCE_TRIG, OUTPUT);
  pinMode(PIN_DISTANCE_ECHO, INPUT);

  // BLE 세팅
  if(!BLE.begin()){
    Serial.println("Error: Setting BLE failed! \n");
    while(1);
  }

  BLE.setLocalName(LOCAL_NAME);
  BLE.setDeviceName(DEVICE_NAME);
  BLE.setAdvertisedService(customService);

  customService.addCharacteristic(customCharacteristic);
  BLE.addService(customService);

  Serial.println("BLE device is now advertising \n");
  BLE.advertise();

  // 동작 모두 초기화
  operationType = "";
  initialize();
}

void loop(){
  // BLE 연결 요청이 있는지 항상 확인
  BLEDevice central = BLE.central();
  String address = central.address();

  if(!central){
    return;
  }

  // BLE 연결 요청이 있으면 진행
  operationType = "A";
  Serial.println("Connected to central: " + address);

  while(central.connected()) {
    String receivedMessage = receiveMessage();

    if(receivedMessage != ""){
      String parts_receivedMessage[MAX_NUM_OF_PARTS_SPLIT];
      int numOfParts = split(receivedMessage, '_', parts_receivedMessage, MAX_NUM_OF_PARTS_SPLIT);

      if(parts_receivedMessage[0] == "[P]"){
        if(parts_receivedMessage[1] == "d"){  // 연결 해제 요청 시 연결 끊음
          break;
        }

        if(parts_receivedMessage[1] == "c"){  // 동작 유형 변경 요청을 받으면
          if(numOfParts >= 3){
            initialize();
            String type = parts_receivedMessage[2];
            operationType = type;
            Serial.println("type: " + type);
          }
        }
      }
    }
    
    execute();
  }

  // BLE 연결 종료
  central.disconnect();
  operationType = "";
  initialize();
  Serial.println("Disconnected from central: " + address + "\n");
}

//

void initialize(){  // 동작 초기화 함수
  mini_servo.write(0);

  digitalWrite(PIN_BASIC_LED_RED, LOW);
  digitalWrite(PIN_BASIC_LED_GREEN, LOW);

  analogWrite(PIN_RGB_LED_RED, 0);
  analogWrite(PIN_RGB_LED_GREEN, 0);
  analogWrite(PIN_RGB_LED_BLUE, 0);
}

void execute(){  // 설정한 동작 유형대로 실행하는 함수
  if(operationType == ""){
    return;
  }

  initialize();
  
  if(operationType == "A"){  // 버튼 A를 눌렀을 때의 동작
    // 2개의 LED를 모두 ON
    digitalWrite(PIN_BASIC_LED_RED, HIGH);
    digitalWrite(PIN_BASIC_LED_GREEN, HIGH);
  }
  else if(operationType == "B"){  // 버튼 B를 눌렀을 때의 동작
    long distanceCm = getDistanceCm();

    if(distanceCm < 10){  // 거리 센서의 10cm 이내에 물체가 있으면
      // RGB LED를 조종
      analogWrite(PIN_RGB_LED_RED, 255);
      analogWrite(PIN_RGB_LED_GREEN, 0);
      analogWrite(PIN_RGB_LED_BLUE, 0);
      delay(100);

      analogWrite(PIN_RGB_LED_RED, 0);
      analogWrite(PIN_RGB_LED_GREEN, 255);
      analogWrite(PIN_RGB_LED_BLUE, 0);
      delay(100);

      analogWrite(PIN_RGB_LED_RED, 0);
      analogWrite(PIN_RGB_LED_GREEN, 0);
      analogWrite(PIN_RGB_LED_BLUE, 255);
      delay(100);
    }
    else{
      // Basic LED 2개를 조종
      digitalWrite(PIN_BASIC_LED_RED, HIGH);
      digitalWrite(PIN_BASIC_LED_GREEN, LOW);
      delay(100);

      digitalWrite(PIN_BASIC_LED_RED, LOW);
      digitalWrite(PIN_BASIC_LED_GREEN, HIGH);
      delay(100);
    }
  }
  else if(operationType == "C"){  // 버튼 C를 눌렀을 때의 동작
    // 서보 모터의 회전 각도를 10도로 변경
    mini_servo.write(10);
    delay(500);

    // 서보 모터의 회전 각도를 20도로 변경
    mini_servo.write(20);
    delay(500);

    mini_servo.write(30);
    delay(500);

    mini_servo.write(0);
    delay(500);
  }
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

/*
bool sendMessage(String message){  // 메시지 보내는 함수
  bool result = false;
  message = "[E]_" + message + "_";
  customCharacteristic.writeValue(message.c_str());

  Serial.println("Sent: " + message);
  result = true;
  return result;
}
*/

String receiveMessage(){  // 메시지 받는 함수
  String result = "";

  if(!customCharacteristic.written()){
    return result;
  }

  const uint8_t * message_uint8t_arr = customCharacteristic.value();
  const char* message_char_arr = (const char*)message_uint8t_arr;
  String message_str(message_char_arr);
  String receivedMessage = "";

  for(int a=0; a<message_str.length(); a++){
    char c1 = message_str.charAt(a);
    bool allowedChar = false;

    if(c1 >= 'a' && c1 <= 'z'){
      allowedChar = true;
    }
    else if(c1 >= 'A' && c1 <= 'Z'){
      allowedChar = true;
    }
    else if(c1 >= '0' && c1 <= '9'){
      allowedChar = true;
    }
    else{
      for(int b=0; b<NUM_OF_ALLOWED_CHARS; b++){
        char c2 = allowingChars[b];

        if(c1 == c2){
          allowedChar = true;
          break;
        }
      }
    }

    if(allowedChar){
      receivedMessage += c1;
    }
  }

  String parts_receivedMessage[MAX_NUM_OF_PARTS_SPLIT];
  int numOfParts = split(receivedMessage, '_', parts_receivedMessage, MAX_NUM_OF_PARTS_SPLIT);

  if(numOfParts < 2){
    return result;
  }

  result = receivedMessage;
  Serial.println("Received: " + receivedMessage);
  return result;
}

//

int split(String input, char delimiter, String result[], int maxParts){  // 문자열을 배열로 분할하는 함수
  int count = 0;
  int startIndex = 0;
  int delimIndex;

  while ((delimIndex = input.indexOf(delimiter, startIndex)) != -1) {
    if (count >= maxParts) break;
    result[count++] = input.substring(startIndex, delimIndex);
    startIndex = delimIndex + 1;
  }

  if (count < maxParts && startIndex < input.length()) {
    result[count++] = input.substring(startIndex);
  }

  return count;
}