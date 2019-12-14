//按鈕手動調整
//外圍led alarm時也可以做效果
//測距
//oled右下的陰影

#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_G4  392

#define A 10
#define B 11
#define C 12
#define D 13

#define PIN_CONFIG 0
#define PIN_STATE 1


// 然後準備歌曲的資料，底下先用個短短的範例。
int melody[] = {
  NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4,
  NOTE_E4, NOTE_D4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_G3,
  NOTE_A3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4,
};

int noteDurations[] = {
  6, 16, 8, 8, 8, 8, 4,
  6, 16, 8, 8, 8, 8, 4,
  6, 16, 8, 8, 8, 8, 4,
  6, 16, 8, 8, 8, 8, 4,
};

int matrix[12][2][4] = {
  //           PIN_CONFIG                  PIN_STATE
  //    A       B       C      D         A     B    C    D
  { {INPUT, INPUT, OUTPUT, OUTPUT}, {0, 0, 1, 0} },
  { {INPUT, INPUT, OUTPUT, OUTPUT}, {0, 0, 0, 1} }, 
  { {INPUT, OUTPUT, OUTPUT, INPUT}, {0, 1, 0, 0} },
  { {INPUT, OUTPUT, OUTPUT, INPUT}, {0, 0, 1, 0} }, 
  { {OUTPUT, OUTPUT, INPUT, INPUT}, {1, 0, 0, 0} },
  { {OUTPUT, OUTPUT, INPUT, INPUT}, {0, 1, 0, 0} }, 
  { {INPUT, OUTPUT, INPUT, OUTPUT}, {0, 1, 0, 0} }, 
  { {INPUT, OUTPUT, INPUT, OUTPUT}, {0, 0, 0, 1} }, 
  { {OUTPUT, INPUT, OUTPUT, INPUT}, {1, 0, 0, 0} }, 
  { {OUTPUT, INPUT, OUTPUT, INPUT}, {0, 0, 1, 0} }, 
  { {OUTPUT, INPUT, OUTPUT, INPUT}, {1, 0, 0, 0} }, 
  { {OUTPUT, INPUT, OUTPUT, INPUT}, {0, 0, 0, 1} }  
};

//
//
//
//
//

#include <Wire.h>
#include <SoftwareSerial.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RTC_DS1307 RTC;
SoftwareSerial BTserial(6, 7); // RX | TX
const int DS1307 = 0x68; // Address of DS1307 
//String days[7] = 
//{"Mon  ", "Tue  ", "Wed  ", "Thu  ", "Fri  ", "Sat  ", "Sun  "};
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;


int alarm_hour=12, alarm_minute=0;
int btInput = 0;
int numLED = 0;  //control which LED should turn on

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // HC-05 default serial speed for AT mode is 38400
  BTserial.begin(38400);

  Wire.begin();   //I2C data transfer
    RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
}

void loop() {
  if(hour == alarm_hour && minute == alarm_minute){
      Serial.println("Alarm!!!!!!");
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(4);
      display.print("ALARM!!!");
      display.display();
      play(melody, noteDurations, sizeof(melody) / sizeof(int));
  }

  display.clearDisplay();
  printTime();
  changeLED(second/5);
//  numLED += 1;
//  if(numLED > 20){
//    numLED = 0;
//  }

  if (BTserial.available()){  
        btInput = BTserial.read();
        Serial.println(btInput);
        if(btInput == 100){  //100: start edit time
          setTime();
        }
        if(btInput == 200){ //200: set alarm
          setAlarm();
        }
    }
    delay(970);
}


void setAlarm(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(4);
  display.print("SET  ALARM");
  display.display();
  
  while(btInput != 101){ //101: end set alarm
//    printTime(); //or display something indicating setAlarm
    if (BTserial.available()){
      btInput = BTserial.read();
      Serial.println(btInput);
    }
    if(btInput == 202){ //202: set alarm time
      int n = 0;
      while(n < 2){
        if (BTserial.available()){
          btInput = BTserial.read();
          Serial.println(btInput);
          n++;
        }
        if(n == 1){
          alarm_hour = btInput;
          Serial.println(alarm_hour);
        }
        else if(n == 2){
          alarm_minute = btInput;
          Serial.println(alarm_minute);
        }
      }
    }
  }
}

void setTime(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(4);
  display.print("SET  TIME");
  display.display();
  
  while(btInput != 101){ // 101: end edit time
    if (BTserial.available()){
      btInput = BTserial.read();
      Serial.println(btInput);
    }
    if(btInput == 102){ //102: edit clock time
      int n = 0;
      while(n < 2){
        if (BTserial.available()){
          btInput = BTserial.read();
          Serial.println(btInput);
          n++;
        }
        if(n == 1){
          hour = btInput;
          Serial.println(hour);
        }
        else if(n == 2){
          minute = btInput;
          Serial.println(minute);
        }
        second = 0;
      }
    }
    else if(btInput == 103){ //103: edit clock date
      int n = 0;
      while(n < 3){
        if(BTserial.available()){
          btInput = BTserial.read();
          Serial.println(btInput);
          n++;
        }
        if(n == 1){
          year = btInput;
          Serial.println(year);
        }
        if(n == 2){
          month = btInput;
          Serial.println(month);
        }
        else if(n == 3){
          monthday = btInput;
          Serial.println(monthday);
        }
      }
    }
//    else if(i == 104){ //104: edit weekday
//      if (BTserial.available()){
//          i = BTserial.read();
//          Serial.println(i);
//      }
//      delay(300);
//      week = i;
//      Serial.println(w[week-1]);
//    }
  }
  // The following codes transmits the data to the RTC
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(monthday));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(byte(0));
  Wire.endTransmission();
  // Ends transmission of data
}

void changeLED(int led){
//  Serial.println("led");
//  pinMode( A, matrix[led][PIN_CONFIG][0] );
//  pinMode( B, matrix[led][PIN_CONFIG][1] );
//  pinMode( C, matrix[led][PIN_CONFIG][2] );
//  pinMode( D, matrix[led][PIN_CONFIG][3] );
//  digitalWrite( A, matrix[led][PIN_STATE][0] );
//  digitalWrite( B, matrix[led][PIN_STATE][1] );
//  digitalWrite( C, matrix[led][PIN_STATE][2] );
//  digitalWrite( D, matrix[led][PIN_STATE][3] );
  switch(led){
  case 0:
    pinMode(A, OUTPUT); pinMode(B, INPUT); pinMode(C, INPUT); pinMode(D, OUTPUT);
    digitalWrite(A, 0); digitalWrite(B, 0); digitalWrite(C, 0); digitalWrite(D, 1);
    break;
  case 1:
    pinMode(A, INPUT); pinMode(B, INPUT); pinMode(C, OUTPUT); pinMode(D, OUTPUT);
    digitalWrite(A, 0); digitalWrite(B, 0); digitalWrite(C, 1); digitalWrite(D, 0);
    break;
   case 2:
    pinMode(A, INPUT); pinMode(B, INPUT); pinMode(C, OUTPUT); pinMode(D, OUTPUT);
    digitalWrite(A, 0); digitalWrite(B, 0); digitalWrite(C, 0); digitalWrite(D, 1);
    break;
   case 3:
    pinMode(A, INPUT); pinMode(B, OUTPUT); pinMode(C, OUTPUT); pinMode(D, INPUT);
    digitalWrite(A, 0); digitalWrite(B, 1); digitalWrite(C, 0); digitalWrite(D, 0);
    break;
   case 4:
    pinMode(A, INPUT); pinMode(B, OUTPUT); pinMode(C, OUTPUT); pinMode(D, INPUT);
    digitalWrite(A, 0); digitalWrite(B, 0); digitalWrite(C, 1); digitalWrite(D, 0);
    break;
   case 5:
    pinMode(A, OUTPUT); pinMode(B, OUTPUT); pinMode(C, INPUT); pinMode(D, INPUT);
    digitalWrite(A, 1); digitalWrite(B, 0); digitalWrite(C, 0); digitalWrite(D, 0);
    break;
   case 6:
    pinMode(A, OUTPUT); pinMode(B, OUTPUT); pinMode(C, INPUT); pinMode(D, INPUT);
    digitalWrite(A, 0); digitalWrite(B, 1); digitalWrite(C, 0); digitalWrite(D, 0);
    break;
   case 7:
    pinMode(A, INPUT); pinMode(B, OUTPUT); pinMode(C, INPUT); pinMode(D, OUTPUT);
    digitalWrite(A, 0); digitalWrite(B, 1); digitalWrite(C, 0); digitalWrite(D, 0);
    break;
   case 8:
    pinMode(A, INPUT); pinMode(B, OUTPUT); pinMode(C, INPUT); pinMode(D, OUTPUT);
    digitalWrite(A, 0); digitalWrite(B, 0); digitalWrite(C, 0); digitalWrite(D, 1);
    break;
   case 9:
    pinMode(A, OUTPUT); pinMode(B, INPUT); pinMode(C, OUTPUT); pinMode(D, INPUT);
    digitalWrite(A, 1); digitalWrite(B, 0); digitalWrite(C, 0); digitalWrite(D, 0);
    break;
   case 10:
    pinMode(A, OUTPUT); pinMode(B, INPUT); pinMode(C, OUTPUT); pinMode(D, INPUT);
    digitalWrite(A, 0); digitalWrite(B, 0); digitalWrite(C, 1); digitalWrite(D, 0);
    break;
   case 11:
    pinMode(A, OUTPUT); pinMode(B, INPUT); pinMode(C, INPUT); pinMode(D, OUTPUT);
    digitalWrite(A, 1); digitalWrite(B, 0); digitalWrite(C, 0); digitalWrite(D, 0);
    break;
  }
}

void printTime(){
  readTime();
  display.setCursor(0, 0);
  display.setTextSize(3);
  if(hour<10)
    display.print("0");
  display.print(hour);
  display.print(":");
  if(minute<10)
    display.print("0");
  display.print(minute);
  display.setTextSize(1);
  display.print(" ");
  display.setTextSize(2);
  if(second<10)
    display.print("0");
  display.print(second);
//
  display.setCursor(0, 33);
  display.setTextSize(2);
  display.print(month);
  display.print("/");
  display.print(monthday);
  display.print(" ");
  display.print("20");
  display.print(year);
//  
  display.display();
//  display.clearDisplay();
}

void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}

void play(int *melody, int *noteDurations, int num){
  for(int note = 0; note < num; note++){
    int noteDuration = 3000 / noteDurations[note];
    tone(5, melody[note], noteDuration);

    delay(noteDuration * 1.30);
  }
}
