
/* Confetti

By: Mark Kriegsman

Modified By: Andrew Tuline

Date: July 2015

Confetti flashes colours within a limited hue. It's been modified from Mark's original to support a few variables. It's a simple, but great looking routine.

*/


#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.
#include "confetti.h"

namespace confetti_ns {
  unsigned long previousMillis;                                 // Store last time the strip was updated.
  // Define variables used by the sequences.
  uint8_t  thisfade = 8;                                        // How quickly does it fade? Lower = slower fade rate.
  int       thishue = 50;                                       // Starting hue.
  uint8_t   thisinc = 1;                                        // Incremental value for rotating hues
  uint8_t   thissat = 100;                                      // The saturation, where 255 = brilliant colours.
  uint8_t   thisbri = 255;                                      // Brightness of a sequence. Remember, max_bright is the overall limiter.
  int       huediff = 256;                                      // Range of random #'s to use for hue
  uint8_t thisdelay = 5;                                        // We don't need much delay (if any)
};

using namespace confetti_ns;

void Confetti::confetti() {                                             // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(Confetti::leds, Confetti::num_leds, thisfade);                    // Low values = slower fade.
  int pos = random16(Confetti::num_leds);                               // Pick an LED at random.
  leds[pos] += CHSV((thishue + random16(huediff))/4 , thissat, thisbri);  // I use 12 bits for hue so that the hue increment isn't too quick.
  thishue = thishue + thisinc;                                // It increments here.
} // confetti()


void Confetti::change_me() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  uint8_t secondHand = (millis() / 1000) % 15;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: thisinc=1; thishue=192; thissat=255; thisfade=2; huediff=256; break;  // You can change values here, one at a time , or altogether.
      case  5: thisinc=2; thishue=128; thisfade=8; huediff=64; break;
      case 10: thisinc=1; thishue=random16(255); thisfade=1; huediff=16; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 15: break;                                                                // Here's the matching 15 for the other one.
    }
  }
} // ChangeMe()

void Confetti::loop () {
  change_me();                                                 // Check the demo loop for changes to the variables.

  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    confetti();
  }
  FastLED.show();  
} // loop()

