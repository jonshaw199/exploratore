/* sinelon
 *
 * By: Mark Kriegsman
 *
 * Modified by: Andrew Tuline
 *
 * Date: February 2015
 *
 * This uses the built in beat in FastLED to move a dot back and forth. In this case, it uses two beats added together for more randomness.
 *
 */


#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.
#include "sinelon.h"

namespace sinelon_ns {
    // Global variables can be changed on the fly.
    uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.

    CRGBPalette16 currentPalette;
    CRGBPalette16 targetPalette;
    TBlendType    currentBlending = LINEARBLEND;                                // NOBLEND or LINEARBLEND

    // Define variables used by the sequences.
    uint8_t thisbeat =  23;                                       // Beats per minute for first part of dot.
    uint8_t thatbeat =  28;                                       // Combined the above with this one.
    uint8_t thisfade =   32;                                       // How quickly does it fade? Lower = slower fade rate.
    uint8_t  thissat = 255;                                       // The saturation, where 255 = brilliant colours.
    uint8_t  thisbri = 255;                                       // Brightness of a sequence.
    int        myhue =   0;

    int    thisdelay = 50;
};

using namespace sinelon_ns;

void Sinelon::loop () {

  EVERY_N_MILLISECONDS(100) {
    uint8_t maxChanges = 24;
    nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);   // AWESOME palette blending capability.
  }

  EVERY_N_SECONDS(5) {                                        // Change the target palette to a random one every 5 seconds.
    static uint8_t baseC = random8();                         // You can use this as a baseline colour if you want similar hues in the next line.
    targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
  }

  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    sinelon();                                                // Call our sequence.
  }

  FastLED.show();

} // loop()

void Sinelon::sinelon() {                                              // a colored dot sweeping back and forth, with fading trails

  fadeToBlackBy( leds, num_leds, thisfade);
  int pos1 = beatsin16(thisbeat,0,num_leds);
  int pos2 = beatsin16(thatbeat,0,num_leds);

  leds[(pos1+pos2)/2] += ColorFromPalette(currentPalette, myhue++, thisbri, currentBlending);

} // sinelon()
