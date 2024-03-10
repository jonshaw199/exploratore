#ifndef EXPLORATORE_PATTERN_H
#define EXPLORATORE_PATTERN_H

#include <FastLED.h>
#include "arduino_routine.hpp"

class Pattern : public ArduinoRoutine
{
public:
    Pattern(CRGB *leds, uint16_t num_leds, std::string name = "");
    virtual ~Pattern() = default;
    virtual void setup();
    virtual void loop();
    static uint64_t micros();

protected:
    CRGB *leds;
    uint16_t num_leds;
};

#endif // EXPLORATORE_PATTERN_H
