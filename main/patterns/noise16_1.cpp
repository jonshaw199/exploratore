/* noise16_1
 * 
 * By: Andrew Tuline
 *
 * Date: January, 2017
 *
 * A 16 bit noise routine with palettes. This was signficantly modified from a routine originally by Stefan Petrick.
 * 
 */

#include "FastLED.h"                                          // FastLED library.
#include "noise16_1.h"

namespace noise16_1_ns {
	uint8_t max_bright = 128;
	CRGBPalette16 currentPalette = PartyColors_p;
	CRGBPalette16 targetPalette;
	TBlendType    currentBlending = LINEARBLEND;                                // NOBLEND or LINEARBLEND
	uint8_t maxChanges = 24;      // Number of tweens between palettes.
};

using namespace noise16_1_ns;

void Noise161::loop() {
  EVERY_N_MILLISECONDS(50) {
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  // Blend towards the target palette
  }

  EVERY_N_SECONDS(5) {             // Change the target palette to a random one every 5 seconds.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

  noise16_1();
  
  FastLED.show();
  
} // loop()

void Noise161::noise16_1() {                                            // moves a noise up and down while slowly shifting to the side

  uint16_t scale = 1000;                                      // the "zoom factor" for the noise

  for (uint16_t i = 0; i < num_leds; i++) {

    uint16_t shift_x = beatsin8(5);                           // the x position of the noise field swings @ 17 bpm
    uint16_t shift_y = millis() / 100;                        // the y position becomes slowly incremented
    

    uint16_t real_x = (i + shift_x)*scale;                    // the x position of the noise field swings @ 17 bpm
    uint16_t real_y = (i + shift_y)*scale;                    // the y position becomes slowly incremented
    uint32_t real_z = millis() * 20;                          // the z position becomes quickly incremented
    
    uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;   // get the noise data and scale it down

    uint8_t index = sin8(noise*3);                           // map LED color based on noise data
    uint8_t bri   = noise;

    leds[i] = ColorFromPalette(currentPalette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }

} // noise16_1()

