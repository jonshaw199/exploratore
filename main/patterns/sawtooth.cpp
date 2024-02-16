/* Sawtooth
 *
 * By: Andrew Tuline
 *
 * Date: February, 2018
 *
 * Creating a sawtooth pattern using millis and bpm. It runs at about 440 fps with the configuration below on an Arduino Nano.
 *
 */

#include "FastLED.h"                                          // FastLED library.
#include "sawtooth.h"

namespace sawtooth_ns {
    // Global variables can be changed on the fly.
    uint8_t max_bright = 128;                                     // Overall brightness.
    // Palette definitions
    CRGBPalette16 currentPalette = PartyColors_p;
    CRGBPalette16 targetPalette = PartyColors_p;
    TBlendType    currentBlending = LINEARBLEND;                  // NOBLEND or LINEARBLEND
};

using namespace sawtooth_ns;

void Sawtooth::loop () {

  Serial.println(LEDS.getFPS());
  sawtooth();
  FastLED.show();

} // loop()

void Sawtooth::sawtooth() {

  int bpm = 60;
  int ms_per_beat = 60000/bpm;                                // 500ms per beat, where 60,000 = 60 seconds * 1000 ms
  int ms_per_led = 60000/bpm/num_leds;

  int cur_led = ((millis() % ms_per_beat) / ms_per_led)%(num_leds);     // Using millis to count up the strand, with %num_leds at the end as a safety factor.

  if (cur_led == 0)
   fill_solid(leds, num_leds, CRGB::Black);
  else
    leds[cur_led] = ColorFromPalette(currentPalette, 0, 255, currentBlending);    // I prefer to use palettes instead of CHSV or CRGB assignments.

} // sawtooth()
