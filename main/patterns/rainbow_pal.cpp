/* ripple_pal
 *
 * By: Balázs Suhajda
 * 
 * Modified by: Andrew Tuline
 * 
 * Date: Oct, 2014
 *
 * A cool ripple effect for an LED strip that's been re-written and optimized from the Neopixel version https://gist.github.com/suhajdab/9716635
 *
 */


#include "FastLED.h"                                          // FastLED library.
#include "rainbow_pal.h"

namespace rainbow_pal_ns {
// Initialize changeable global variables.
uint8_t max_bright = 255;                                     // Overall brightness definition. It can be changed on the fly.

CRGBPalette16 currentPalette;
CRGBPalette16 targetPalette;
TBlendType    currentBlending = LINEARBLEND;                                // NOBLEND or LINEARBLEND

uint8_t colour;                                               // Ripple colour is randomized.
int center = 0;                                               // Center of the current ripple.
int step = -1;                                                // -1 is the initializing step.
uint8_t myfade = 255;                                         // Starting brightness.
#define maxsteps 16                                           // Case statement wouldn't allow a variable.
uint8_t fadeval = 128;

uint8_t bgcol = 0;                                            // Background colour rotates.
int thisdelay = 60;                                          // Standard delay value.
};

using namespace rainbow_pal_ns;

void RainbowPal::loop () {

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(3) {
      targetPalette = CRGBPalette16(CHSV(random8(), 255, 32), CHSV(random8(), random8(64)+192, 255), CHSV(random8(), 255, 32), CHSV(random8(), 255, 255)); 
  }

  EVERY_N_MILLISECONDS(thisdelay) {                                   // FastLED based non-blocking delay to update/display the sequence.
    ripple();
    FastLED.show();
  }

} // loop()

void RainbowPal::ripple() {

  fadeToBlackBy(leds, num_leds, fadeval);                             // 8 bit, 1 = slow, 255 = fast
  
  switch (step) {

    case -1:                                                          // Initialize ripple variables.
      center = random(num_leds);
      colour = random8();
      step = 0;
      break;

    case 0:
      leds[center] = ColorFromPalette(currentPalette, colour, myfade, currentBlending);
      
      step ++;
      break;

    case maxsteps:                                                    // At the end of the ripples.
      step = -1;
      break;

    default:                                                          // Middle of the ripples.
      leds[(center + step + num_leds) % num_leds] += ColorFromPalette(currentPalette, colour, myfade/step*2, currentBlending);       // Simple wrap from Marc Miller
      leds[(center - step + num_leds) % num_leds] += ColorFromPalette(currentPalette, colour, myfade/step*2, currentBlending);
      step ++;                                                         // Next step.
      break;  
  } // switch step
  
} // ripple()
