/*H**********************************************************************
* FILENAME :        twinkle.h            
*
* DESCRIPTION :
*       Draws a twinkle, with random colors
*
* AUTHOR :    Adrian Polo (apolo)       START DATE :  3/12/2022
*
*H*/
#include <FastLED.h>

#define NUM_COLORS 5
static const CRGB TwinkleColors[NUM_COLORS] = 
{
    CRGB::Red,
    CRGB::Blue,
    CRGB::Purple,
    CRGB::Green,
    CRGB::Orange
};

void DrawTwinkle(int num_leds, CRGB leds[]) {

    for (int i = 0; i < num_leds / 2; i++ ) {
        leds[random(num_leds)] = TwinkleColors[random(NUM_COLORS)];
    }
    FastLED.show();
}
