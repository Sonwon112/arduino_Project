// 초음파 센서로 1단~5단 후진을 감지
// 로터리 엔코더로 핸들이 어떻게 얼마나 돌아갔는지 감지하여 유니티 프로그램과 시리얼 통신(몇단인지도 송신하여 속도 제어)
// 버튼(추가구매 필요)을 통해 엑셀과 브레이크 제어
// 안드로이드와 블루투스 통신으로 현재 몇단인지 전송
#include <Thread.h>

// 초음파 센서
int sonarTrig[] = {2,3,4,5,6,7};
int sonarEcho[] = {8,9,10,11,12,13};

// 로터리 엔코더
int rotaryCLK = 22;
int rotaryDT = 23;

// 블루투스 모듈
int blueTX = 17;
int blueRX = 18;

int oldCLK = 0;
int oldDT = 0;
int direction = 0;

Thread myThread = Thread();

void clacDirection(){
  
  int newCLK = digitalRead(rotaryCLK);
  int newDT = digitalRead(rotaryDT);
  Serial.print("newDT : ");
  Serial.println(newDT);
  Serial.print("oldDT : ");
  Serial.println(oldDT);

  Serial.print("newCLK : ");
  Serial.println(newCLK);
  Serial.print("oldCLK : ");
  Serial.println(oldCLK);

  Serial.println("");
  oldCLK = newCLK;
  oldDT = newDT;
  // Serial.println(direction);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(rotaryCLK, INPUT);
  pinMode(rotaryDT, INPUT);

  Serial.begin(9600);
  myThread.onRun(clacDirection);
  myThread.setInterval(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myThread.shouldRun()) myThread.run();
}
