/* matrix_pal_demo
 *
 * Originally By: funkboxing LED
 *
 * Modified a LOT by: Andrew Tuline
 *
 * Date: July, 2015
 * 
 * Various coloured characters going up/down the strand, a la 'The Matrix'. This highly modified version uses non-blocking
 * delays as well as colorPalette lookups and other variables such as direction, speed and background colours.
 *
 */

#include "FastLED.h"                                          // FastLED library.
#include "matrix_pal.h"

namespace matrix_pal_ns { 
	// Palette definitions
	CRGBPalette16 currentPalette;
	CRGBPalette16 targetPalette;
	TBlendType    currentBlending = LINEARBLEND;

	// Initialize global variables for sequences.
	int      thisdelay =  50;                                     // A delay value for the sequence(s)
	uint8_t    palIndex =  95;
	uint8_t    thissat = 255;
	int        thisdir =   0;
	uint8_t thisbright = 255;
	bool        huerot =   0;                                     // Does the hue rotate? 1 = yes
	uint8_t      bgclr =   0;
	uint8_t      bgbri =   0;
};

using namespace matrix_pal_ns;

void MatrixPal::loop () {
  ChangeMe();

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_MILLISECONDS(thisdelay) {
    matrix();
  }
  
  FastLED.show();
} // loop()


void MatrixPal::matrix() {                                               // One line matrix
  if (huerot) palIndex++;
  
  if (random8(90) > 80) {
    if (thisdir == 0)
      leds[0] = ColorFromPalette(currentPalette, palIndex, thisbright, currentBlending); 
    else
      leds[num_leds-1] = ColorFromPalette( currentPalette, palIndex, thisbright, currentBlending);
  } else {
    if (thisdir == 0)
      leds[0] = CHSV(bgclr, thissat, bgbri); 
    else
      leds[num_leds-1] = CHSV(bgclr, thissat, bgbri);
  }

  if (thisdir == 0) {
    for (int i = num_leds-1; i >0 ; i-- ) leds[i] = leds[i-1];
  } else {
    for (int i = 0; i < num_leds-1 ; i++ ) leds[i] = leds[i+1];
  }
} // matrix()

// Also RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.

void MatrixPal::ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 25;                // Change '25' to a different value to change length of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.

  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: thisdelay=50; palIndex=95; bgclr=140; bgbri=4; huerot=0; break;
      case  5: targetPalette = OceanColors_p; thisdir=1; bgbri=0; huerot=1; break;
      case 10: targetPalette = LavaColors_p; thisdelay=30; palIndex=0; bgclr=50; bgbri=8; huerot=0; break;
      case 15: targetPalette = ForestColors_p; thisdelay=80; bgbri = 16; bgclr=96; palIndex=random8(); break;
      case 20: palIndex=random8(); huerot=1; break;
      case 25: break;
    }
  }
} // ChangeMe()
