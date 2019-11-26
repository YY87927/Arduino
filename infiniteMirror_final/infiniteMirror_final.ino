#include <FastLED.h>

#define PIN 8
#define NUM 23
#define BRIGHTNESS 100
#define X 255
#define TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_OF_MODE 6
CRGB leds[NUM];
boolean change=false;
volatile uint8_t mode=0;
int i, j, input, last_input, last_input2, average;
uint8_t gHue = 0;
//uint8_t gCurrentPatternNumber = 0;
//typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

void changeMode();
void turnOff();
void mode1();
void mode2();
void mode3();
void mode4();
void mode5();

int rainbow16[16][3]={{255,   0,   0},    //紅
                      {255,  85,   0},    //橙
                      {255, 170,   0},    //
                      {255, 255,   0},    //黃
                      {127, 255,   0},    //
                      {  0, 255,   0},    //綠
                      {  0, 255,  85},    //
                      {  0, 255, 170},    //
                      {  0, 255, 255},    //青
                      {  0, 127, 255},    //
                      {  0,   0, 255},    //藍
                      { 85,   0, 255},    //紫
                      {170,   0, 255},    //
                      {255,   0, 255},    //洋紅
                      {255,   0, 127},    //
                      {255, 255, 255}};   //白

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  FastLED.addLeds<TYPE, PIN, COLOR_ORDER>(leds, NUM).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), changeMode, RISING);

  Serial.begin(115200);
}

void loop() {
  //Serial.println(mode);
  
  if(change){
    delay(500);
    change=false;
    mode+=1;
    mode=mode%NUM_OF_MODE;
  }

  if(!change){
    //Serial.println(change);
  }

  EVERY_N_MILLISECONDS(20){gHue++;}
  
  if(mode==0){
    turnOff();
  }
  else if(mode==1){
    mode1();
  }
  else if(mode==2){
    mode2();  
  }
  else if(mode==3){
    mode3();
  }
  else if(mode==4){
    mode4();
  }
  else if(mode==5){
    mode5();
 //   Serial.println(mode);
  }
  //FastLED.show();
  //delay(200);
}

void mode5(){
  int k;
  for(j = 0; j < 3; j++ ){ 
    memset(leds, 0, NUM * 3);
    for(int k = 0; k < 256; k+=5){ 
      for(int i = 0; i < NUM; i++ ){
        Serial.println("3");
        switch(j){ 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastLED.show();
    }
    FastLED.clear();
    for(k = 255; k >= 0; k-=5) { 
      for(i = 0; i < NUM; i++ ) {
        switch(j){ 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastLED.show();
    }
    FastLED.clear();
  }
}

void mode4(){
  int i;
  for(i=0; i<NUM; i+=3){
    leds[i].r=X; leds[i].g=0; leds[i].b=0;
    leds[i+1].r=0; leds[i+1].g=X; leds[i+1].b=0;
    leds[i+2].r=0; leds[i+2].g=0; leds[i+2].b=X;
  }
  FastLED.show();
  delay(100);

  for(i=0; i<NUM; i+=3){
    leds[i]=CRGB(0, X, 0);
    leds[i+1]=CRGB(0, 0, X);
    leds[i+2]=CRGB(X, 0, 0);
  }
  FastLED.show();
  delay(100);
  
  for(i=0; i<NUM; i+=3){
    leds[i]=CRGB(0, 0, X);
    leds[i+1]=CRGB(X, 0, 0);
    leds[i+2]=CRGB(0, X, 0);
  }
  FastLED.show();
  delay(100);

  mode%=NUM_OF_MODE;
  FastLED.clear();
}

void mode3(){
  
  for( j = 0; j < 3; j++) 
  { 
   for( i = 0 ; i < NUM; i++ ) 
   {
     memset(leds, 0, NUM * 3);
     switch(j)
     { 
      case 0: leds[i]=CRGB(X, 0, 0); break;
      case 1: leds[i]=CRGB(0, X, 0); break;
      case 2: leds[i]=CRGB(0, 0, X); break;
     }
     FastLED.show();
     delay(10);
    }
  }
  FastLED.clear();
}

void mode2(){
  input = analogRead(A3);
  int16_t led_num = 0;
  Serial.println(input);
  led_num = float((input - 502))/2;
  if(led_num >= 11)
    led_num = 11;
  if(led_num <= 0)
    led_num = 0; 
  for(uint8_t i=0; i<led_num; i++)
  {
     int16_t r;
     r = 40*i;
     if(r >= 255)
        r = 255;
     leds[i]=CRGB(r, 0, 255-r);
     leds[21-i]=CRGB(r, 0, 255-r);
  }
  FastLED.show();
  FastLED.clear();
}


void mode1(){
  for(int i=0;i<NUM;i++)  //輪流讀表設定LED顏色
  {
    leds[i] = CRGB(rainbow16[i][0],rainbow16[i][1],rainbow16[i][2]);
    FastLED.show(); 
    delay(200);
  }
  FastLED.clear();
}


void turnOff(){
  int i;
  for(i=0; i<NUM; i++){
    leds[i]=CRGB(0, 0, 0);
  }
  FastLED.show();
}

void changeMode(){
  delay(500);
  change=true;
  /*
  mode++;
  mode%=NUM_OF_MODE;
  */
  //delay(1000);
}
