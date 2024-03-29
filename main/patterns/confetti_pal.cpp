/* confetti_pal
 *
 * By: Mark Kriegsman
 *
 * Modified By: Andrew Tuline
 *
 * Date: July, 2015
 *
 * Confetti flashes colours within a limited hue. It's been modified from Mark's original to support palettes and a few other variables. It's a simple, but great looking routine.
 *
 */


#include "FastLED.h"                                          // FastLED library.
#include "confetti_pal.h"

namespace confetti_pal_ns {
  CRGBPalette16 currentPalette;
  CRGBPalette16 targetPalette;
  TBlendType    currentBlending = LINEARBLEND;                                // NOBLEND or LINEARBLEND
  // Define variables used by the sequences.
  uint8_t  thisfade = 8;                                        // How quickly does it fade? Lower = slower fade rate.
  int       thishue = 50;                                       // Starting hue.
  uint8_t   thisinc = 1;                                        // Incremental value for rotating hues
  uint8_t   thissat = 100;                                      // The saturation, where 255 = brilliant colours.
  uint8_t   thisbri = 255;                                      // Brightness of a sequence. Remember, max_bright is the overall limiter.
  int       huediff = 256;                                      // Range of random #'s to use for hue
  uint8_t thisdelay = 5;                                        // We don't need much delay (if any)
};

using namespace confetti_pal_ns;

void ConfettiPal::loop () {
  ChangeMe();                                                 // Check the demo loop for changes to the variables.

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24; 
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    confetti_pal();
  }
  
  FastLED.show();

} // loop()



void ConfettiPal::confetti_pal() {                                         // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, num_leds, thisfade);                    // Low values = slower fade.
  int pos = random16(num_leds);                               // Pick an LED at random.
  leds[pos] = ColorFromPalette(currentPalette, thishue + random16(huediff)/4 , thisbri, currentBlending);
  thishue = thishue + thisinc;                                // It increments here.
  
} // confetti_pal()



void ConfettiPal::ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  uint8_t secondHand = (millis() / 1000) % 15;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: targetPalette = OceanColors_p; thisinc=1; thishue=192; thissat=255; thisfade=2; huediff=255; break;  // You can change values here, one at a time , or altogether.
      case  5: targetPalette = LavaColors_p; thisinc=2; thishue=128; thisfade=8; huediff=64; break;
      case 10: targetPalette = ForestColors_p; thisinc=1; thishue=random16(255); thisfade=1; huediff=16; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 15: break;                                         // Here's the matching 15 for the other one.
    }
  }
  
} // ChangeMe()


// RainbowColors_p, RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p
