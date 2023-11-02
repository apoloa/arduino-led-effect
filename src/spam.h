#include <FastLED.h>
#include <Arduino.h>
#include "breath.h"

#define NUM_COLORS 5
static const CRGB DoorColor[NUM_COLORS] =
    {
        CRGB::Red,
        CRGB::OrangeRed,
        CRGB::Green,
        CRGB::Purple,
        CRGB::Orange};

void DrawSpam(int num_leds, CRGB leds[])
{
    for (int i = 0; i < 4; i++)
    {
        redFlash(num_leds, leds);
    }

    breatheEffect(num_leds, leds, DoorColor[random(NUM_COLORS)]);
}