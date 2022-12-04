#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>



#define NUM_LEDS 150
#define DATA_PIN 7
#define SECOND_DATA_PIN 9
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS] = {0};
CRGB leds2[NUM_LEDS] = {0};

#include "marquee.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.addLeds<LED_TYPE,SECOND_DATA_PIN,COLOR_ORDER>(leds2, NUM_LEDS);
  FastLED.setBrightness(16); 
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("loop");
  DrawMarquee(NUM_LEDS, leds);
  DrawMarquee(NUM_LEDS, leds2);
  FastLED.show();
}