#include <Arduino.h>
#include <FastLED.h>

void DrawCandle(int num_leds, CRGB leds[])
{
    CRGB colorVela = CRGB(255, 147, 41);
    static byte brightness = 200;
    brightness = random(50, 120); // Ajusta para mayor/menor variación
    FastLED.setBrightness(brightness);
    fill_solid(leds, num_leds, colorVela);
    FastLED.show();
    delay(random(50, 150)); // Ajusta para mayor/menor velocidad de parpadeo
}