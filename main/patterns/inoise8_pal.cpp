/* inoise8_pal_demo
 *
 * By: Andrew Tuline
 *
 * Date: August, 2016
 *
 * This short sketch demonstrates some of the functions of FastLED, including:
 *
 * Perlin noise
 * Palettes
 * Palette blending
 * Alternatives to blocking delays
 * Beats (and not the Dr. Dre kind, but rather the sinewave kind)
 *
 * Refer to the FastLED noise.h and lib8tion.h routines for more information on these functions.
 * 
 */
 
 
#include "FastLED.h"
#include "inoise8_pal.h"

namespace inoise8_pal_ns {
	// Global variables can be changed on the fly.
	uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.
	 
	CRGBPalette16 currentPalette(CRGB::Black);
	CRGBPalette16 targetPalette(OceanColors_p);
	TBlendType    currentBlending;                                // NOBLEND or LINEARBLEND 
	 
	int16_t dist = random16(12345);                                          // A random number for our noise generator.
	uint16_t xscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
	uint16_t yscale = 30;                                         // Wouldn't recommend changing this on the fly, or the animation will be really blocky.
	uint8_t maxChanges = 24;                                      // Value for blending between palettes.
};

using namespace inoise8_pal_ns;

void Inoise8Pal::loop() {
  EVERY_N_MILLISECONDS(10) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
    inoise8_pal();                                                            // Update the LED array with noise at the new location
  }
 
  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
 
  FastLED.show();
  
} // loop()

void Inoise8Pal::inoise8_pal() {
  
  for(int i = 0; i < num_leds; i++) {                                      // Just ONE loop to fill up the LED array as all of the pixels change.
    uint8_t index = inoise8(i*xscale, dist+i*yscale) % 255;                // Get a value from the noise function. I'm using both x and y axis.
    leds[i] = ColorFromPalette(currentPalette, index, 255, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  
  dist += beatsin8(10,1,4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
                                                                           // In some sketches, I've used millis() instead of an incremented counter. Works a treat.
} // fillnoise8()
