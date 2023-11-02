#ifndef HALLOWEEN_BREATH_EFFECT_H
#define HALLOWEEN_BREATH_EFFECT_H
#include <Arduino.h>
#include <FastLED.h>

void breatheEffect(int num_leds, CRGB leds[], CRGB color)
{
    static byte breatheDirection = 1;
    static byte breatheValue = 0;
    int breatheSpeed = 8; // Ajusta para una respiración más rápida o lenta
    FastLED.setBrightness(70);
    fill_solid(leds, num_leds, CRGB(color.r * breatheValue / 255, color.g * breatheValue / 255, color.b * breatheValue / 255));
    FastLED.show();

    breatheValue += breatheDirection * breatheSpeed;
    if (breatheValue >= 255 || breatheValue <= 0)
    {
        breatheDirection = -breatheDirection;
        delay(150); // Pequeña pausa en la "cima" y "fondo" de la respiración
    }
    delay(35);
}

void redFlash(int num_leds, CRGB leds[])
{
    FastLED.setBrightness(255);
    fill_solid(leds, num_leds, CRGB::Red);
    FastLED.show();
    delay(70); // Duración del destello
    fill_solid(leds, num_leds, CRGB::Black);
    FastLED.show();
    delay(70); // Pausa entre destellos
}

void DrawBreath(int num_leds, CRGB leds[])
{
    breatheEffect(num_leds, leds, CRGB::OrangeRed);
    if (random(10) > 7)
    { // Aproximadamente 3 de 10 veces ejecutará el flash
        redFlash(num_leds, leds);
    }
}

#endif // HALLOWEEN_BREATH_EFFECT_H