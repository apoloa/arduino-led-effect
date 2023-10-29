#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

const char *app_name = "Christmas Light";

#define NUM_LEDS 150
#define DATA_1_PIN 2 // FUNC 
#define DATA_2_PIN 4 // FUNC
#define DATA_3_PIN 5 // FUNC 
#define DATA_4_PIN 13 // FUNC
#define DATA_5_PIN 14
#define DATA_6_PIN 19
#define DATA_7_PIN 26
#define DATA_8_PIN 33
#define DATA_9_PIN 32
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

CRGB leds[9][NUM_LEDS] = {0};


#include <Oled.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "AP_HOME";
const char *password = "AP19921995";
AsyncWebServer server(80);

OledManager g_OledManager;

#include "marquee.h"
#include "twinkle.h"

enum class Effect
{
  White,
  Twinkle,
  Marquee
};

Effect g_ActualEffect = Effect::White;
bool clean = true;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(DATA_1_PIN, OUTPUT); 
  pinMode(DATA_2_PIN, OUTPUT); 
  pinMode(DATA_3_PIN, OUTPUT); 
  pinMode(DATA_4_PIN, OUTPUT); 
  pinMode(DATA_5_PIN, OUTPUT); 
  pinMode(DATA_6_PIN, OUTPUT); 
  pinMode(DATA_7_PIN, OUTPUT); 
  pinMode(DATA_8_PIN, OUTPUT); 
  pinMode(DATA_9_PIN, OUTPUT); 
  
  FastLED.addLeds<LED_TYPE, DATA_1_PIN, COLOR_ORDER>(leds[0], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_2_PIN, COLOR_ORDER>(leds[1], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_3_PIN, COLOR_ORDER>(leds[2], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_4_PIN, COLOR_ORDER>(leds[3], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_5_PIN, COLOR_ORDER>(leds[4], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_6_PIN, COLOR_ORDER>(leds[5], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_7_PIN, COLOR_ORDER>(leds[6], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_8_PIN, COLOR_ORDER>(leds[7], NUM_LEDS);
  FastLED.addLeds<LED_TYPE, DATA_9_PIN, COLOR_ORDER>(leds[8], NUM_LEDS);

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
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/plain", "Hello, world"); });

  server.on("/twinkle", HTTP_POST, [](AsyncWebServerRequest *request)
            { 
              g_ActualEffect = Effect::Twinkle;
              clean = true;
              request->send(200); });

  server.on("/marquee", HTTP_POST, [](AsyncWebServerRequest *request)
            { 
              g_ActualEffect = Effect::Marquee;
              clean = true;
              request->send(200); });

  server.begin();
  g_OledManager.showIP(WiFi.localIP().toString());

  delay(1000);
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  if (clean) {
    switch (g_ActualEffect) {
      case Effect::Twinkle:
        g_OledManager.showEffect("Twinkle");
        break;
      case Effect::Marquee:
        g_OledManager.showEffect("Marquee");
        break;
    }
    FastLED.clear();
    clean = false;
  }

  switch (g_ActualEffect)
  {
    case Effect::White:
    leds[0][0] = CRGB::White;
    leds[1][0] = CRGB::White;
    leds[2][0] = CRGB::White;
    leds[3][0] = CRGB::White;
    leds[4][0] = CRGB::White;
    leds[5][0] = CRGB::White;
    leds[6][0] = CRGB::White;
    leds[7][0] = CRGB::White;
    FastLED.show();
      break;
  case Effect::Twinkle:
    Serial.println("twinkle");
    
    FastLED.clear(false); // We want to clear the colors matrix without applying yet.
    for (int i = 0; i < 9; i++ ) {
        DrawTwinkle(NUM_LEDS, leds[i]);
    }
    delay(1000);
    break;
  case Effect::Marquee:
    Serial.println("marquee");
    for (int i = 0; i < 9; i++ ) {
        DrawTwinkle(NUM_LEDS, leds[i]);
    }
    FastLED.show();
    break;
  }
}