#ifndef HALLOWEEN_DOOR_EFFECT_H
#define HALLOWEEN_DOOR_EFFECT_H

#include <FastLED.h>

void flashEffect(int startPos, int length, CRGB color, CRGB *leds, int numLeds)
{
    for (int i = 0; i < 3; i++)
    {
        for (int i = startPos; i < startPos + length && i < numLeds; i++)
        {
            leds[i] = color;
        }
        FastLED.show();
        delay(70);
        for (int i = startPos; i < startPos + length && i < numLeds; i++)
        {
            leds[i] = CRGB::Black;
        }
        FastLED.show();
        delay(70);
    }
}

void breathEffect(int startPos, int length, CRGB color, CRGB *leds, int numLeds)
{
    for (int j = 0; j < 256; j += 5)
    {
        for (int i = startPos; i < startPos + length && i < numLeds; i++)
        {
            leds[i] = color;
            leds[i].fadeToBlackBy(255 - j);
        }
        FastLED.show();
        delay(3);
    }
    delay(24);
    for (int j = 255; j >= 0; j -= 5)
    {
        for (int i = startPos; i < startPos + length && i < numLeds; i++)
        {
            leds[i] = color;
            leds[i].fadeToBlackBy(255 - j);
        }
        FastLED.show();
        delay(3);
    }
}

#define HALLOWEEN_COLORS 4
static const CRGB HalloweenColors[HALLOWEEN_COLORS] =
    {
        CRGB::Red,
        CRGB::Purple,
        CRGB::OrangeRed,
        CRGB::Green};

void DrawHalloweenDoor(int numLeds, CRGB *leds)
{
    FastLED.clear();
    int startPosition = random(numLeds);
    int length = random(10, 40);
    CRGB color = HalloweenColors[random(HALLOWEEN_COLORS)];

    int chosenEffect = random(2);
    switch (chosenEffect)
    {
    case 0:
        flashEffect(startPosition, length, color, leds, numLeds);
        break;
    case 1:
        breathEffect(startPosition, length, color, leds, numLeds);
        break;
    }
}

#endif // HALLOWEEN_DOOR_EFFECT_H
