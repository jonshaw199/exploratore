/* noise16_2
 * 
 * By: Andrew Tuline
 *
 * Date: January, 2017
 *
 * A 16 bit noise routine with palettes. This was significantly modified from a routine originally by Stefan Petrick.
 * 
 */

#include "FastLED.h"                                          // FastLED library.
#include "noise16_2.h"

namespace noise16_2_ns {
	uint8_t max_bright = 128;
	CRGBPalette16 currentPalette = PartyColors_p;
	CRGBPalette16 targetPalette;
	TBlendType    currentBlending = LINEARBLEND;                                // NOBLEND or LINEARBLEND
	uint8_t maxChanges = 24;      // Number of tweens between palettes.
};

using namespace noise16_2_ns;

void Noise162::loop() {
  EVERY_N_MILLISECONDS(50) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  // Blend towards the target palette
  }

  EVERY_N_SECONDS(5) {             // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

  noise16_2();
  
  FastLED.show();
  
} // loop()

void Noise162::noise16_2() {                                            // just moving along one axis = "lavalamp effect"

  uint8_t scale = 1000;                                       // the "zoom factor" for the noise

  for (uint16_t i = 0; i < num_leds; i++) {

    uint16_t shift_x = millis() / 10;                         // x as a function of time
    uint16_t shift_y = 0;

    uint32_t real_x = (i + shift_x) * scale;                  // calculate the coordinates within the noise field
    uint32_t real_y = (i + shift_y) * scale;                  // based on the precalculated positions
    uint32_t real_z = 4223;
    
    uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;    // get the noise data and scale it down

    uint8_t index = sin8(noise*3);                            // map led color based on noise data
    uint8_t bri   = noise;

    leds[i] = ColorFromPalette(currentPalette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.

  }
  
} // noise16_2()



