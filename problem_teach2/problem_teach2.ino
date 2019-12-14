#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FastLED.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define PIN 8
#define NUM 23
#define TYPE WS2812
#define COLOR_ORDER GRB

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
CRGB leds[NUM];

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  FastLED.addLeds<TYPE, PIN, COLOR_ORDER>(leds, NUM).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(50);

  display.display();
  delay(2000);
  display.clearDisplay();
  FastLED.clear();

}

void loop() {
  // put your main code here, to run repeatedly:
  while (!Serial.available()){}
  int input = Serial.parseInt(); //read int or parseFloat for ..float...
  char junk = Serial.read();
  Serial.println(input);

  for(int i=0; i<NUM && i<input; i++){
    leds[i] = CRGB(255, 255, 255);
  }
  FastLED.show();
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print(input);
  display.display();
}
