// 초음파 센서로 1단~5단 후진을 감지
// 로터리 엔코더로 핸들이 어떻게 얼마나 돌아갔는지 감지하여 유니티 프로그램과 시리얼 통신(몇단인지도 송신하여 속도 제어)
// 버튼(추가구매 필요)을 통해 엑셀과 브레이크 제어
// 안드로이드와 블루투스 통신으로 현재 몇단인지 전송
#include <Thread.h>

// 초음파 센서 핀넘버
//2,8 -> r단
//3,9 -> 1단
//4,10 -> 2단
//5,11 -> 3단
//6,12 -> 4단
//7,13 -> 5단
int sonarTrig[] = {2,3,4,5,6,7};
int sonarEcho[] = {8,9,10,11,12,13};
float distance[] = {0,0,0,0,0,0};

Thread myThread = Thread();

// 로터리 엔코더
int rotaryCLK = 14;
int rotaryDT = 15;
int rotarySW = 16;

// 블루투스 모듈
int blueTX = 17;
int blueRX = 18;


void changeLevel(){
  for(int i = 0; i < 6; i++){
    digitalWrite(sonarTrig[i], LOW);
    digitalWrite(sonarEcho[i], LOW);
    delayMicroseconds(2);
    digitalWrite(sonarTrig[i], HIGH);
    delayMicroseconds(10);
    digitalWrite(sonarTrig[i], LOW);

    unsigned long duration = pulseIn(sonarEcho[i],HIGH);
    distance[i] = duration / 29.0/ 2.0;
    // Serial.print(i);
    // Serial.print(" : ");
    // Serial.println(distance[i]);
  }

  if(distance[0]  < 3){//r단
    Serial.println(distance[0]);
    Serial.println("R단");
  }
  else if(distance[1] < 3){//1단
    Serial.println(distance[1]);
    Serial.println("1단");
  }
  else if(distance[2] < 3){//2단
    Serial.println(distance[2]);
    Serial.println("2단");
  }
  else if(distance[3] < 3){//3단
    Serial.println(distance[3]);
    Serial.println("3단");
  }
  else if(distance[4] < 3){//4단
    Serial.println(distance[4]);
    Serial.println("4단");
  }
  else if(distance[5] < 3){//5단
    Serial.println(distance[5]);
    Serial.println("5단");
  }
  else{//아무것도 아닐때, 즉 중립
    Serial.println("중립");
  }
}


void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 6; i++){
    pinMode(sonarTrig[i], OUTPUT);
    pinMode(sonarEcho[i], INPUT);
  }
  Serial.begin(9600);
  myThread.onRun(changeLevel);
  myThread.setInterval(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myThread.shouldRun())
		myThread.run();
  	
}
