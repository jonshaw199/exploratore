/* easing
 *
 * By: Andrew Tuline
 *
 * Date: August, 2015
 *
 * This boring display demonstrates the easing capability of FastLED. The Red LED starts out slow, speeds up and then slows down when it gets to the end.
 *
 * It uses uint8_t variables and may not work correctly on longer strands . . as noted by GitHub user fahrvergnuunen.
 *
 * easeOutVal = ease8InOutQuad(easeInVal);                       // Start with easeInVal at 0 and then go to 255 for the full easing.
 * ledNum = lerp8by8(0, num_leds, easeOutVal);                   // Map it to the number of LED's you have.
 *
 * Reference:
 * 
 * https://github.com/FastLED/FastLED/wiki/High-performance-math
 * 
 * 
 * Ideas:
 *  - Ease from 128 to 255 to throw something in the air
 *  - Ease from 255 to 128 and reverse direction for it to fall back.
 *  - Reduce the lerp8 value after each cycle to simulate a bouncing ball.
 *
 */
#include "FastLED.h"                                          // FastLED library. Please use the latest development version.
#include "easing.h"

namespace easing_ns {
	// Global variables can be changed on the fly.
	uint8_t max_bright = 128;                                     // Overall brightness definition. It can be changed on the fly.
	int thisdelay = 20;

	uint8_t easeOutVal = 0;
	uint8_t easeInVal  = 0;
	uint8_t lerpVal    = 0;
};

using namespace easing_ns;


void Easing::loop() {
  
  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    ease();
  }
  
  FastLED.show();
  
} // loop()



void Easing::ease() {
  easeOutVal = ease8InOutQuad(easeInVal);                     // Start with easeInVal at 0 and then go to 255 for the full easing.
  easeInVal++;

  lerpVal = lerp8by8(0, num_leds, easeOutVal);                // Map it to the number of LED's you have.

  leds[lerpVal] = CRGB::Red;
  fadeToBlackBy(leds, num_leds, 16);                          // 8 bit, 1 = slow fade, 255 = fast fade
  
} // ease()


