#include <FastLED.h>

void DrawDown(int num_leds, CRGB leds[])
{
    FastLED.clear();
    fill_solid(leds, num_leds, CRGB::Black);
    FastLED.show();
}