/* dots
 *
 * By: John Burroughs
 *
 * Modified by: Andrew Tuline
 * 
 * Date: July, 2015
 * 
 * Similar to dots by John Burroughs, but uses the FastLED beatsin8() function instead.
 *
 */

#include "FastLED.h"                                          // FastLED library.
#include "dot_beat.h"

namespace dot_beat_ns {
	// Define variables used by the sequences.
	int   thisdelay =   10;                                       // A delay value for the sequence(s)
	uint8_t   count =   0;                                        // Count up to 255 and then reverts to 0
	uint8_t fadeval = 224;                                        // Trail behind the LED's. Lower => faster fade.
	uint8_t bpm = 30;
};

using namespace dot_beat_ns;

void DotBeat::loop () {
  uint8_t inner = beatsin8(bpm, num_leds/4, num_leds/4*3);    // Move 1/4 to 3/4
  uint8_t outer = beatsin8(bpm, 0, num_leds-1);               // Move entire length
  uint8_t middle = beatsin8(bpm, num_leds/3, num_leds/3*2);   // Move 1/3 to 2/3

  leds[middle] = CRGB::Purple;
  leds[inner] = CRGB::Blue;
  leds[outer] = CRGB::Aqua;

  nscale8(leds,num_leds,fadeval);                             // Fade the entire array. Or for just a few LED's, use  nscale8(&leds[2], 5, fadeval);

  FastLED.show();
} // loop()

