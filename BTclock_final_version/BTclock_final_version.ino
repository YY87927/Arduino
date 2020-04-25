#define A 10
#define B 11
#define C 12
#define D 13

#define PIN_CONFIG 0
#define PIN_STATE 1


// 然後準備歌曲的資料，底下先用個短短的範例。
const uint16_t melody[] PROGMEM = {
  392, 392, 330, 294, 330, 294, 262,
  330, 294, 262, 220, 196, 220, 196,
  220, 220, 262, 220, 262, 294, 330,
  294, 294, 392, 392, 330, 294, 262,
};

const uint16_t noteDurations[] PROGMEM= {
  6, 16, 8, 8, 8, 8, 4,
  6, 16, 8, 8, 8, 8, 4,
  6, 16, 8, 8, 8, 8, 4,
  6, 16, 8, 8, 8, 8, 4,
};

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
const int DS1307 = 0x68; // Address of RTC 
//String days[7] = 
//{"Mon  ", "Tue  ", "Wed  ", "Thu  ", "Fri  ", "Sat  ", "Sun  "};
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;

int note = 0;   //to turn of alarm: set note = sizeof(melody) / sizeof(int)
bool timeMode = true;  //switch between ultra mode and time mdoe
int alarm_hour=12, alarm_minute=0;
bool alarm_on= false;
int btInput = 0;
int numLED = 0;  //control which LED should turn on
//button1 = 2 enter setting mode
//button2 = 3 shift to different parameter in setting mode or enter ultra mode
//button3 = 4 increase value in setting mode or stop alarm
//trig = 8;  echo = 9;

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

  pinMode (8, OUTPUT);
}

void loop() {
  if(hour == alarm_hour && minute == alarm_minute && alarm_on){
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(4);
      display.print("ALARM!!!");
      display.display();
      play();
  }
  if(digitalRead(3)){
    timeMode = !timeMode;
  }
  
  if(timeMode){
    if(digitalRead(2)){
      delay(700);
      settingMode();
    }
    
    readTime();
    display.clearDisplay();
    printTime();
    changeLED(second/5);
  
    if (BTserial.available()){  
          btInput = BTserial.read();
          Serial.println(btInput);
          if(btInput == 100){  //100: start edit time
            Serial.println("setTime");
            setTime();
          }
          if(btInput == 200){ //200: set alarm
            setAlarm();
          }
      }
      delay(970); 
  }
  if(!timeMode){
    float duration;
    int distance;
    digitalWrite(8, HIGH);
    delay(10);
    digitalWrite(8, LOW);
    duration = pulseIn (9, HIGH);
    distance = (duration/2)/29;
    Serial.print("d = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(1000);
    printDistance(distance);
  }
}

void printTime(){
  Serial.println(second);
  display.setCursor(0, 2);
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
  display.setCursor(0, 35);
  display.setTextSize(2);
  display.print(month);
  display.print("/");
  display.print(monthday);
  display.print(" ");
  display.print("20");
  display.print(year);
//  
  display.display();
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
