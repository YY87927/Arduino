/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>
#include <RF24_config.h>
#include <FastLED.h>

RF24 radio(7, 8); // CE, CSN

#define LED_PIN     5
#define NUM_LEDS    23
#define BRIGHTNESS  10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

const byte address[5] = "00001";

void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.setChannel(10);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
//  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
//  radio.setAutoAck(false);

//  delay( 3000 ); // power-up safety delay
//  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
//  FastLED.setBrightness(  BRIGHTNESS );
}

void loop() {
//  CRGB data[NUM_LEDS];
//  for(int i=0; i<NUM_LEDS; i++){
//    leds[i] = CRGB(255, 0, 0);
//    data[i] = leds[i];
//    radio.write(&data, sizeof(data));
//    FastLED.show();
//    delay(500);
//  }
//  
//  for(int i=0; i<NUM_LEDS; i++){
//    leds[i] = CRGB(0, 0, 0);
//    data[i] = leds[i];
//    radio.write(&data, sizeof(data));
//    FastLED.show();
//    delay(500);
//  }

  char text[32] = "Hello";
  radio.write(&text, sizeof(text));
  
  delay(500);
}
