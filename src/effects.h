#include <Arduino.h>

enum class Effect
{
    White,
    Twinkle,
    Marquee,
    RedFlash,
    Breath,
    Candle,
    Ghost,
    HalloweenDoor,
    Down,
    Span,
    None,
};

struct EffectMapEntry
{
    String effectName;
    Effect effectValue;
};

EffectMapEntry effectMap[] = {
    {"White", Effect::White},
    {"Twinkle", Effect::Twinkle},
    {"Marquee", Effect::Marquee},
    {"RedFlash", Effect::RedFlash},
    {"Breath", Effect::Breath},
    {"Ghost", Effect::Ghost},
    {"HalloweenDoor", Effect::HalloweenDoor},
    {"Span", Effect::Span},
    {"Down", Effect::Down},
    {"Candle", Effect::Candle}};

String getEffectName(Effect effect)
{
    for (uint8_t i = 0; i < sizeof(effectMap) / sizeof(effectMap[0]); i++)
    {
        if (effectMap[i].effectValue == effect)
        {
            return effectMap[i].effectName;
        }
    }
    return "Unknown"; // Retorna None
}

Effect stringToEffect(const String effectName)
{
    for (uint8_t i = 0; i < sizeof(effectMap) / sizeof(effectMap[0]); i++)
    {
        String effectNameToCheck = effectMap[i].effectName;
        effectNameToCheck.toUpperCase();
        if (effectNameToCheck == effectName)
        {
            return effectMap[i].effectValue;
        }
    }
    return Effect::None; // Retorna None
}
