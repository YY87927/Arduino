#include <FastLED.h>

#define PIN 8
#define NUM 13
#define BRIGHTNESS 100
#define X 255
#define TYPE WS2812
#define COLOR_ORDER GRB
#define NUM_OF_MODE 3
CRGB leds[NUM];

int increase(int);

int seconds = 0;
int seconds2 = 0;

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  FastLED.addLeds<TYPE, PIN, COLOR_ORDER>(leds, NUM).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  int i;
  for(i=0; i<NUM; i++){
    leds[i]=CRGB(0, 0, 0);
  }
  FastLED.show();


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  seconds = increase(seconds);
  
  if(seconds<NUM){
    leds[seconds].r = X;  leds[seconds].g = 0;  leds[seconds].b = 0;
  }
  
  else if(seconds>=NUM && seconds<=NUM*2){
    leds[seconds].r = 0;  leds[seconds].g = X;  leds[seconds].b = 0; 
  }
  
  else if(seconds>=NUM*2 && seconds<=NUM*3){
    leds[seconds].r = 0;  leds[seconds].g = 0;  leds[seconds].b = X;
  }

  Serial.println(seconds);
  FastLED.show();
}

int increase(int seconds){
  delay(1000);
  //Serial.print("**");
  //Serial.println(seconds);
  return seconds+1;
}
