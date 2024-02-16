
/* rainbow_march

By: Andrew Tuline

Date: Nov, 2014

Updated: June, 2018

Update:

1.1 Remove original delay and added EVERY_N_MILLISECONDS
1.2 Remove EVERY_N_MILLISECONDS and use millis() for timing. Also demonstrate beat8 and beatsin8.


Description

Rainbow marching up the strand. Very basic, but oh so popular. Oh look, we don't need to add a 'wheel' routine.

If you want something really funky, try generating sequences with palettes, especially palettes you can change on the flly.

*/


#include "FastLED.h"                                          // FastLED library.
#include "rainbow_march.h"

namespace rainbow_march_ns {
	// Initialize changeable global variables.
	uint8_t max_bright = 255;                                     // Overall brightness definition. It can be changed on the fly.
};

using namespace rainbow_march_ns;

void RainbowMarch::loop () {

  rainbow_march(200, 10);
  FastLED.show();
  
} // loop()

void RainbowMarch::rainbow_march(uint8_t thisdelay, uint8_t deltahue) {     // The fill_rainbow call doesn't support brightness levels.

  uint8_t thishue = millis()*(255-thisdelay)/255;             // To change the rate, add a beat or something to the result. 'thisdelay' must be a fixed value.
  
// thishue = beat8(50);                                       // This uses a FastLED sawtooth generator. Again, the '50' should not change on the fly.
// thishue = beatsin8(50,0,255);                              // This can change speeds on the fly. You can also add these to each other.
  
  fill_rainbow(leds, num_leds, thishue, deltahue);            // Use FastLED's fill_rainbow routine.

} // rainbow_march()
