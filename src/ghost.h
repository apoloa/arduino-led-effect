#include <FastLED.h>

void DrawGhost(int num_leds, CRGB leds[])
{
    static int posicion = 0;
    static int direccion = 1;

    fill_solid(leds, num_leds, CRGB::Black); // Limpia la tira
    leds[posicion] = CRGB::White;

    FastLED.show();

    posicion += direccion;
    if (posicion == num_leds - 1 || posicion == 0)
    {
        direccion = -direccion; // Cambia de dirección
    }

    delay(50); // Ajusta para mayor/menor velocidad
}