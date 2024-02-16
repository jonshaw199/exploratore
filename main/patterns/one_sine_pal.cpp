/* one_sine_pal
 *
 * By: Andrew Tuline
 *
 * Date: January, 2017
 * 
 * Forget using delay() statements or counting pixels up and down the strand of LED's. This example demonstrates just a bit of what can be done using basic high school math
 * by using a simple sinewave.
 * 
 * You can use a sine wave to go back and forth up a strand of LED's. You can shift the phase of a sine wave to move along a strand. You can clip the top of that sine wave
 * to just display a certain value (or greater). You can add palettes to that sine wave so that you aren't stuck with CHSV values and so on.
 * 
 * It shows that you don't neeed a pile of for loops, delays or counting pixels in order to come up with a decent animation.
 * 
 */


// Use qsuba for smooth pixel colouring and qsubd for non-smooth pixel colouring
#define qsubd(x, b)  ((x>b)?b:0)                   // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)                          // Analog Unsigned subtraction macro. if result <0, then => 0

#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.
#include "one_sine_pal.h"

namespace one_sine_pal_ns {
	uint8_t max_bright = 128;                                     // Overall brightness definition. It can be changed on the fly.
	// Initialize changeable global variables. Play around with these!!!
	int8_t thisspeed = 8;                                         // You can change the speed of the wave, and use negative values.
	uint8_t allfreq = 32;                                         // You can change the frequency, thus distance between bars.
	int thisphase = 0;                                            // Phase change value gets calculated.
	uint8_t thiscutoff = 192;                                     // You can change the cutoff value to display this wave. Lower value = longer wave.
	int thisdelay = 30;                                           // You can change the delay. Also you can change the allspeed variable above. 
	uint8_t bgclr = 0;                                            // A rotating background colour.
	uint8_t bgbright = 10;                                        // Brightness of background colour
	// Palette definitions
	CRGBPalette16 currentPalette = LavaColors_p;
	CRGBPalette16 targetPalette;
	TBlendType    currentBlending = LINEARBLEND;
};

using namespace one_sine_pal_ns;

void OneSinePal::loop () {
//  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    one_sine_pal(millis()>>4);
  }

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }
  
  FastLED.show();

} // loop()



void OneSinePal::one_sine_pal(uint8_t colorIndex) {                                       // This is the heart of this program. Sure is short.
  
  thisphase += thisspeed;                                                     // You can change direction and speed individually.
  
  for (int k=0; k<num_leds-1; k++) {                                          // For each of the LED's in the strand, set a brightness based on a wave as follows:
    int thisbright = qsubd(cubicwave8((k*allfreq)+thisphase), thiscutoff);    // qsub sets a minimum value called thiscutoff. If < thiscutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
    leds[k] = CHSV(bgclr, 255, bgbright);                                     // First set a background colour, but fully saturated.
    leds[k] += ColorFromPalette( currentPalette, colorIndex, thisbright, currentBlending);    // Let's now add the foreground colour.
    colorIndex +=3;
  }
  
  bgclr++;
  
} // one_sine_pal()
