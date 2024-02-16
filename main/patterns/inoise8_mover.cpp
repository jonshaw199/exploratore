/* inoise8_mover
 *
 * By: Andrew Tuline
 *
 * Date: February, 2017
 *
 * We've used sine waves and counting to move pixels around a strand. In this case, I'm using Perlin Noise to move a pixel up and down the strand.
 * 
 * The advantage here is that it provides random natural movement without requiring lots of fancy math by joe programmer.
 *
 */
 
 
#include "FastLED.h"
#include "inoise8_mover.h"

namespace inoise8_mover_ns {
	// Global variables can be changed on the fly.
	uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.

	CRGBPalette16 currentPalette=LavaColors_p;
	CRGBPalette16 targetPalette=OceanColors_p;
	TBlendType    currentBlending;                                // NOBLEND or LINEARBLEND 

	int16_t dist = random16(12345);                                          // A moving location for our noise generator.
	uint16_t xscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
	uint16_t yscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
	uint8_t maxChanges = 24;                                      // Value for blending between palettes.
};

using namespace inoise8_mover_ns;

void Inoise8Mover::loop() {
  
  EVERY_N_MILLISECONDS(10) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
    
    inoise8_mover();                                          // Update the LED array with noise at the new location
    fadeToBlackBy(leds, num_leds, 4);     
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
 
  FastLED.show();
  
} // loop()


 
void Inoise8Mover::inoise8_mover() {

  uint8_t locn = inoise8(xscale, dist+yscale) % 255;          // Get a new pixel location from moving noise.
  uint8_t pixlen = map(locn,0,255,0,num_leds);                // Map that to the length of the strand.
  leds[pixlen] = ColorFromPalette(currentPalette, pixlen, 255, LINEARBLEND);   // Use that value for both the location as well as the palette index colour for the pixel.

  dist += beatsin8(10,1,4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.                                             

} // inoise8_mover()
;
