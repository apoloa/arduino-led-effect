#include <Arduino.h>
#define FASTLED_I NTERNAL
#include <FastLED.h>

const char *app_name = "Christmas Light";

#define NUM_LEDS 300
#define DATA_2_PIN 4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

#include <Oled.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "AP_HOME";
const char *password = "AP19921995";
AsyncWebServer server(80);

OledManager g_OledManager;

#include "effects.h"
#include "marquee.h"
#include "twinkle.h"
#include "red-flash.h"
#include "breath.h"
#include "candle.h"
#include "ghost.h"
#include "halloween-door.h"
#include "down.h"
#include "spam.h"

Effect g_ActualEffect = Effect::White;
bool clean = true;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    pinMode(DATA_2_PIN, OUTPUT);

    FastLED.addLeds<LED_TYPE, DATA_2_PIN, COLOR_ORDER>(leds, NUM_LEDS);

    FastLED.setBrightness(255);
    pinMode(LED_BUILTIN, OUTPUT);

    g_OledManager.init(app_name);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!");
        return;
    }
    server.on("/effect", HTTP_POST, [](AsyncWebServerRequest *request)
              {
    String effectName;
    if (request->hasParam("effect")) {
        String effectName = request->getParam("effect")->value();
        effectName.toUpperCase();
        Effect effect = stringToEffect(effectName);
        if(effect != Effect::None) {
            g_ActualEffect = effect;
            clean = true;
        }
        
    }
    request->send(200); });

    server.begin();
    g_OledManager.showIP(WiFi.localIP().toString());

    delay(1000);
}

void loop()
{
    // put your main code here, to run repeatedly:

    if (clean)
    {
        FastLED.setBrightness(255);
        g_OledManager.showEffect(getEffectName(g_ActualEffect));
        FastLED.clear();
        clean = false;
    }

    switch (g_ActualEffect)
    {
    case Effect::White:
        FastLED.clear();
        fill_solid(leds, NUM_LEDS, CRGB::White);
        FastLED.show();
        break;
    case Effect::Twinkle:
        Serial.println("twinkle");
        FastLED.clear(false); // We want to clear the colors matrix without applying yet.
        DrawTwinkle(NUM_LEDS, leds);
        delay(1000);
        break;
    case Effect::Marquee:
        Serial.println("marquee");
        DrawTwinkle(NUM_LEDS, leds);
        FastLED.show();
        break;
    case Effect::RedFlash:
        DrawRedFlash(NUM_LEDS, leds, 3);
        break;
    case Effect::Breath:
        DrawBreath(NUM_LEDS, leds);
        break;
    case Effect::Candle:
        DrawCandle(NUM_LEDS, leds);
        break;
    case Effect::Ghost:
        DrawGhost(NUM_LEDS, leds);
        break;
    case Effect::HalloweenDoor:
        DrawHalloweenDoor(NUM_LEDS, leds);
        break;
    case Effect::Span:
        DrawSpam(NUM_LEDS, leds);
        break;
    case Effect::Down:
        DrawDown(NUM_LEDS, leds);
        break;
    }
}