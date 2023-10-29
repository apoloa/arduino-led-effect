/*H**********************************************************************
* FILENAME :        marquee.h            
*
* DESCRIPTION :
*       Draws and old movie threatre style marquee, but in color
*
* AUTHOR :    Adrian Polo (apolo)       START DATE :  3/12/2022
*
*H*/

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void DrawMarquee(int num_leds, CRGB leds[]) 
{
    static byte j = HUE_BLUE;
    j += 4; 
    byte k = j;

    // The following code will be the same as the fill_rainbow from FastLED

    CRGB c;

    for (int i = 0; i < num_leds; i++) {
        leds[i] = c.setHue(k+=8);
    }

    static int scroll = 0;
    scroll++;

    for (int i = scroll % 5; i < num_leds -1; i+=5 ) {
        leds[i] = CRGB::Black;
    }

    delay(30);

}
