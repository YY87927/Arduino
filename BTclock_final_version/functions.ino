void setAlarm(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(4);
  display.print("SET  ALARM");
  display.display();
  
  while(btInput != 101){ //101: end set alarm
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
    if(btInput == 203){ //203: alarm on
      alarm_on = true;
    }
    if(btInput == 204){ //204: alarm off
      alarm_on = false;
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

void increaseDigit(int changeWhichDigit){
  switch(changeWhichDigit){
      case 0:
        hour += 1;  hour %= 24;  break;
      case 1:
        minute += 1;  minute %= 60;  break;
       case 2:
        month += 1;  month %= 12;  break;
       case 3:
        monthday += 1;
        if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
          monthday %= 31;
        else if (month==2)
          monthday %= 29;
        else
          monthday %= 30;
        break;
       case 4:
        year += 1;  year %= 50;  break;
        //
       case 5:
        alarm_hour += 1;  alarm_hour %= 24;  break;
       case 6:
        alarm_minute += 1;  alarm_minute %= 60;  break;
       case 7:
        alarm_on = !alarm_on;  break;
  }
}

void settingMode(){
  int changeWhichDigit = 0; //0=hour, 1=minute, 2=month, 3=day, 4=year, 5=alarmHour, 6=alarmMinute, 7=alarmOnOff
  while(digitalRead(2) == 0){
    if(digitalRead(3) == 1){
      delay(500);
      changeWhichDigit +=1;
      changeWhichDigit %= 8;
      Serial.println(changeWhichDigit);
    }
    if(digitalRead(4) == 1){
      delay(500);
      increaseDigit(changeWhichDigit);
    }
    display.clearDisplay();
    if(changeWhichDigit < 5){
      printTime();
    }
    else{
      display.setCursor(0, 2);
      display.setTextSize(3);
      if(alarm_hour<10)
        display.print("0");
      display.print(alarm_hour);
      display.print(":");
      if(alarm_minute<10)
        display.print("0");
      display.print(alarm_minute);
      display.setCursor(0, 35);
      display.setTextSize(2);
      display.print("alarm: ");
      if(alarm_on){
        display.print("On");
      }
      else
        display.print("Off");
    }
    switch(changeWhichDigit){
      case 0: //hour
        display.drawRect(0, 0, 35, 26, WHITE);
        display.display();
        break;
      case 1: //minute
        display.drawRect(52, 0, 35, 26, WHITE);
        display.display();
        break;
       case 2: //month
        display.drawRect(0, 32, 10, 19, WHITE);
        display.display();
        break;
       case 3: //monthday
        display.drawRect(22, 32, 25, 19, WHITE);
        display.display();
        break;
       case 4:
        display.drawRect(56, 32, 51, 19, WHITE);
        display.display();
        break;
        //
       case 5:
        display.drawRect(0, 0, 35, 26, WHITE);
        display.display();
        break;
       case 6:
        display.drawRect(52, 0, 35, 26, WHITE);
        display.display();
        break;
       case 7:
        display.drawRect(81, 32, 38, 20, WHITE);
        display.display();
        break;
    }
  }
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
}

void play(){
  for(note = 0; note < 28; note++){
    int noteDuration = 3000 / pgm_read_word(&noteDurations[note]);
    tone(5, pgm_read_word(&melody[note]), noteDuration);
    if(digitalRead(4) == 1){
      stopAlarm();
    }
    delay(noteDuration * 1.30);
  }
}

void stopAlarm(){
  note = sizeof(melody) / sizeof(int);
  alarm_on = false;
}

void printDistance(int distance){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.print("d=");
  display.print(distance);
  display.setCursor(0, 33);
  display.print("cm");
  display.display();
}
