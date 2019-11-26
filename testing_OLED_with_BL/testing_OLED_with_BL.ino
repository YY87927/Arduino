/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <SoftwareSerial.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
int hour=0, minute=0, second=0, day=1, month=1, week=1;
int m[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
String w[7] = {"Mon  ", "Tue  ", "Wed  ", "Thu  ", "Fri  ", "Sat  ", "Sun  "};
const int inter_time = 1000;
int alarm_hour=12, alarm_minute=0;
bool NL = true;
int i = 0;
SoftwareSerial BTserial(2, 3); // RX | TX


void setup() {
  Serial.begin(9600);
  // HC-05 default serial speed for AT mode is 38400
  BTserial.begin(38400);

  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  //OCR1A = 100;
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
}


void loop() {
  if(hour == alarm_hour && minute == alarm_minute){
      Serial.println("Alarm!!!!!!");
//      play(melody, noteDurations, sizeof(melody) / sizeof(int));
  }

  // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
//        c = BTserial.read();
//        Serial.write(c);
        i = BTserial.read();
        Serial.println(i);
        if(i == 100){  //100: start edit time
          editTime();
        }
        if(i == 200){ //200: set alarm
          setAlarm();
        }
    }

}

void setAlarm(){
  while(i != 101){ //101: end set alarm
    //printTime();
    if (BTserial.available()){
      i = BTserial.read();
      Serial.println(i);
    }
    if(i == 202){ //202: set alarm time
      int n = 0;
      while(n < 2){
        if (BTserial.available()){
          i = BTserial.read();
          Serial.println(i);
          n++;
        }
        if(n == 1){
          alarm_hour = i;
          Serial.println(alarm_hour);
        }
        else if(n == 2){
          alarm_minute = i;
          Serial.println(alarm_minute);
        }
      }
    }
  }
}

void editTime(){

  Serial.println("editTime");
  
  while(i != 101){ // 101: end edit time
    //printTime();
    if (BTserial.available()){
      i = BTserial.read();
      Serial.println(i);
    }
    if(i == 102){ //102: edit clock time
      int n = 0;
      while(n < 2){
        if (BTserial.available()){
          i = BTserial.read();
          Serial.println(i);
          n++;
        }
        if(n == 1){
          hour = i;
          Serial.println(hour);
        }
        else if(n == 2){
          minute = i;
          Serial.println(minute);
        }
        second = 0;
      }
    }
    else if(i == 103){ //103: edit clock date
      int n = 0;
      while(n < 2){
        if(BTserial.available()){
          i = BTserial.read();
          Serial.println(i);
          n++;
        }
        if(n == 1){
          month = i;
          Serial.println(month);
        }
        else if(n == 2){
          day = i;
          Serial.println(day);
        }
      }
    }
    else if(i == 104){ //104: edit weekday
      if (BTserial.available()){
          i = BTserial.read();
          Serial.println(i);
      }
      delay(300);
      week = i;
      Serial.println(w[week-1]);
    }
  }
}


void printTime(){ 
  if(hour<10){
    Serial.print("0");
    Serial.print(hour);
  }
  else{
    Serial.print(hour); 
  }
//  display.setTextSize(1);
  Serial.print(":");
//  display.setTextSize(3);

  if(minute<10){
    Serial.print("0");
    Serial.print(minute);
  }
  else{
    Serial.print(minute); 
  }
  Serial.print(" ");
  if(second<10){
    Serial.print("0");
    Serial.print(second);
  }
  else{
    Serial.print(second); 
  }
  
  Serial.print(month);
  Serial.print("/");
  Serial.print(day);
  Serial.print(" ");
  Serial.print(w[week-1]);

}

ISR(TIMER1_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
   //interrupt commands here
   Serial.println();
   addTime();
   printTime();
}

void addTime(){
  second++;
  if(second>=60){
    second=0;
    minute++;
  }
  if(minute>=60){
    minute=0;
    hour++;
  }
  if(hour>=24){
    hour=0;
    day++;
    week++;
  }
  if(week>7){
    week=1;
  }
  if(day>m[month-1]){
    day=1;
    month++;
  }
  if(month>12){
    month=1;
  }
}
