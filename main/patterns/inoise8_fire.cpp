/* inoise8_fire
 *
 * By: Andrew Tuline
 *
 * Date: January, 2017
 *
 * This super short sketch (just two lines to the algorithm) displays fire thanks to FastLED's Perlin Noise function and Palettes.
 *
 * It needs some tweaking in order to work across a wide range of NUM_LED values, but looks pretty good at 60.
 * 
 */


#include "FastLED.h"
#include "inoise8_fire.h"

namespace inoise8_fire_ns {
	// Global variables can be changed on the fly.
	uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.

	CRGBPalette16 currentPalette = CRGBPalette16(
                                   CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255,4),
                                   CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,                                   
                                   CRGB::DarkOrange,CRGB::Orange, CRGB::Orange, CRGB::Orange,
                                   CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);
	uint32_t xscale = 20;                                          // How far apart they are
	uint32_t yscale = 3;                                           // How fast they move
	uint8_t palette_index = 0;
};

using namespace inoise8_fire_ns;

void Inoise8Fire::loop() {

  inoise8_fire();                                               // I am the god of hell fire and I bring you . . .
  FastLED.show();

} // loop()



void Inoise8Fire::inoise8_fire() {
  
  for(int i = 0; i < num_leds; i++) {
    palette_index = inoise8(i*xscale,millis()*yscale*num_leds/255);                                           // X location is constant, but we move along the Y at the rate of millis()
    leds[i] = ColorFromPalette(currentPalette, min(i*(palette_index)>>6, 255), i*255/num_leds, LINEARBLEND);  // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }                                                                                                   // The higher the value of i => the higher up the palette palette_index (see palette definition).
                                                                                                      // Also, the higher the value of i => the brighter the LED.
} // inoise8_fire()

