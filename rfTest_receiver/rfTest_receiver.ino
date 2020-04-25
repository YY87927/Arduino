/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
//#include <nRF24L01.h>
#include "RF24.h"
#include <FastLED.h>

RF24 radio(7, 8); // CE, CSN

#define LED_PIN     5
#define NUM_LEDS    23
#define BRIGHTNESS  10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

const byte address[] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(10);
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_LOW);
//  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
//  radio.setAutoAck(false);

  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
  int input;
  char data, trash;
  if (radio.available()) {
//    char text[32] = "";
//    radio.read(&text, sizeof(text));
//    Serial.println(text);
//    Serial.println("get");
    radio.read(&data, sizeof(data));
    radio.read(&trash, sizeof(trash));
    input = (int)data;
    input-=48;
    Serial.println(input);
//    Serial.println(leds);
  }
  switch(input){
    case 0:
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB(255, 0, 0);
        FastLED.show();
        delay(500);
      }
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB(0, 0, 0);
      }
      FastLED.show();
      break;
    case 1:
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB(0, 255, 0);
        FastLED.show();
        delay(500);
      }
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB(0, 0, 0);
      }
      FastLED.show();
      break;
    case 2:
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB(0, 0, 255);
        FastLED.show();
        delay(500);
      }
      for(int i=0; i<NUM_LEDS; i++){
        leds[i] = CRGB(0, 0, 0);
      }
      FastLED.show();
      break;
  }
}
