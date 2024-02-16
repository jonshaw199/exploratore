/* juggle_pal
 *
 * Originally by: Mark Kriegsman
 *
 * Modified By: Andrew Tuline
 *
 * Date: February, 2015
 *
 * Juggle just moves some balls back and forth. A single ball could be a Cylon effect. I've added several variables to this simple routine.
 *
 */


#include "FastLED.h"                                          // FastLED library.
#include "juggle_pal.h"

namespace juggle_pal_ns {
	// Global variables can be changed on the fly.
	uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.

	CRGBPalette16 currentPalette  = CRGBPalette16(CRGB::Black);
	CRGBPalette16 targetPalette   = RainbowColors_p;
	TBlendType currentBlending = LINEARBLEND;  
	
	// Routine specific variables
	uint8_t    numdots =   4;                                     // Number of dots in use.
	uint8_t   thisfade =   2;                                     // How long should the trails be. Very low value = longer trails.
	uint8_t   thisdiff =  16;                                     // Incremental change in hue between each dot.
	uint8_t    thishue =   0;                                     // Starting hue.
	uint8_t     curhue =   0;                                     // The current hue
	uint8_t    thissat = 255;                                     // Saturation of the colour.
	uint8_t thisbright = 255;                                     // How bright should the LED/display be.
	uint8_t   thisbeat =   5;                                     // Higher = faster movement.
};

using namespace juggle_pal_ns;
  
void JugglePal::loop() {

  EVERY_N_MILLISECONDS(100) {                                 // AWESOME palette blending capability provided as required.
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   
  }
 
  ChangeMe();
  juggle_pal();
  FastLED.show();                         // Power managed display of LED's.
  
} // loop()



void JugglePal::juggle_pal() {                                           // Several colored dots, weaving in and out of sync with each other
  
  curhue = thishue;                                           // Reset the hue values.
  fadeToBlackBy(leds, num_leds, thisfade);
  
  for( int i = 0; i < numdots; i++) {
    leds[beatsin16(thisbeat+i+numdots,0,num_leds)] += ColorFromPalette(currentPalette, curhue , thisbright, currentBlending);    // Munge the values and pick a colour from the palette
    curhue += thisdiff;
  }
  
} // juggle_pal()



void JugglePal::ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 30;                // IMPORTANT!!! Change '30' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: numdots = 1; thisbeat = 20; thisdiff = 16; thisfade = 2; thishue = 0; break;                  // You can change values here, one at a time , or altogether.
      case 10: numdots = 4; thisbeat = 10; thisdiff = 16; thisfade = 8; thishue = 128; break;
      case 20: numdots = 8; thisbeat =  3; thisdiff =  0; thisfade = 8; thishue=random8(); break;           // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 30: break;
    }
  }
  
} // ChangeMe()

