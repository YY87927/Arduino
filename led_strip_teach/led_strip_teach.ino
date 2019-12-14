#include <FastLED.h>

#define PIN 8
#define NUM 20
#define TYPE WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<TYPE, PIN, COLOR_ORDER>(leds, NUM).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(100);
}

void loop() {
  // put your main code here, to run repeatedly:
//  for(int i=0; i<NUM; i++){
//    leds[i] = CRGB(255, 255, 255);
//  }
//  FastLED.show();
//  delay(2000);
//  for(int i=0; i<NUM; i++){
//    leds[i] = CRGB(0, 0, 0);
//  }
//  FastLED.show();
//  delay(2000);


//  for(int i=0; i<NUM-3; i++){
//    leds[i] = CRGB(255, 0, 0);
//    leds[i+1] = CRGB(0, 255, 0);
//    leds[i+2] = CRGB(0, 0, 255);
//    FastLED.show();
//    delay(100);
//  }


  for(int i=0; i<NUM; i+=3){
    leds[i] = CRGB(255, 0, 0);
    leds[i+1] = CRGB(0, 255, 0);
    leds[i+2] = CRGB(0, 0, 255);
  }
  FastLED.show();
  delay(100);
  for(int i=0; i<NUM; i+=3){
    leds[i] = CRGB(0, 255, 0);
    leds[i+1] = CRGB(0, 0, 255);
    leds[i+2] = CRGB(255, 0, 0);
  }
  FastLED.show();
  delay(100);
  for(int i=0; i<NUM; i+=3){
    leds[i] = CRGB(0, 0, 255);
    leds[i+1] = CRGB(0, 255, 0);
    leds[i+2] = CRGB(255, 0, 0);
  }
  FastLED.show();
  delay(100);
}
