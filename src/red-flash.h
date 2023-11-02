#include <Arduino.h>
#include <FastLED.h>

void DrawRedFlash(int num_leds, CRGB leds[], int width = 1)
{
    int middle = num_leds / 2;
    for (int i = 0; i < middle; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (middle - 1 - i + j >= 0)
            {
                leds[middle - 1 - i + j] = CRGB::Red;
            }
            if (middle + i - j < num_leds)
            {
                leds[middle + i - j] = CRGB::Red;
            }
        }

        FastLED.show();
        delay(2);

        for (int j = 0; j < width; j++)
        {
            if (middle - 1 - i + j >= 0)
            {
                leds[middle - 1 - i + j] = CRGB::Black;
            }
            if (middle + i - j < num_leds)
            {
                leds[middle + i - j] = CRGB::Black;
            }
        }

        FastLED.show();
    }
}