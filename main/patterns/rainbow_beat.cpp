
/* rainbow_beat
 *
 * By: Andrew Tuline
 *
 * Date: July, 2015
 * 
 * A rainbow moving back and forth using FastLED function calls with no delays or 'for' loops. Very simple, yet effective.
 *
 */


#include "FastLED.h"                                          // FastLED library.
#include "rainbow_beat.h"

namespace rainbow_beat_ns {
// Initialize changeable global variables.
uint8_t max_bright = 128;                                     // Overall brightness definition. It can be changed on the fly.
};

using namespace rainbow_beat_ns;

void RainbowBeat::loop () {
  
    rainbow_beat();
    FastLED.show();

} // loop()

void RainbowBeat::rainbow_beat() {
  
  uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
  uint8_t beatB = beatsin8(13, 0, 255);
  fill_rainbow(leds, num_leds, (beatA+beatB)/2, 8);            // Use FastLED's fill_rainbow routine.

} // rainbow_beat()
