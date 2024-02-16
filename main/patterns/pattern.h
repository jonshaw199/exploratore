#ifndef EXPLORATORE_PATTERN_H
#define EXPLORATORE_PATTERN_H

#include <FastLED.h>

class Pattern
{
public:
    Pattern(CRGB *leds, u_int16_t num_leds);
    virtual ~Pattern() = default;
    virtual void setup();
    virtual void loop();
    static uint64_t micros();

protected:
    CRGB *leds;
    uint16_t num_leds;
};

#endif // EXPLORATORE_PATTERN_H
