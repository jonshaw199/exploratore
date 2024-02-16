/* three_sin demo

By: Andrew Tuline

Date: March, 2015

3 sine waves, one for each colour. I didn't take this far.

*/


#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.
#include "three_sin.h"

namespace three_sin_ns {
    // Initialize changeable global variables.
    uint8_t max_bright = 64;                                      // Overall brightness definition. It can be changed on the fly.

    // Initialize global variables for sequences
    uint8_t thisdelay = 50;                                       // A delay value for the sequence(s)

    int wave1=0;                                                  // Current phase is calculated.
    int wave2=0;
    int wave3=0;

    uint8_t inc1 = 2;                                             // Phase shift. Keep it low, as this is the speed at which the waves move.
    uint8_t inc2 = 1;
    uint8_t inc3 = -2;

    uint8_t lvl1 = 80;                                            // Any result below this value is displayed as 0.
    uint8_t lvl2 = 80;
    uint8_t lvl3 = 80;

    uint8_t mul1 = 20;                                            // Frequency, thus the distance between waves
    uint8_t mul2 = 25;
    uint8_t mul3 = 22;
};

using namespace three_sin_ns;

void ThreeSin::loop () {
  ChangeMe();
  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    three_sin();                                              // Improved method of using non-blocking delay
  }
  show_at_max_brightness_for_power();
} // loop()

void ThreeSin::three_sin() {
  wave1 += inc1;
  wave2 += inc2;
  wave3 += inc3;
  for (int k=0; k<num_leds; k++) {
    leds[k].r = qsub8(sin8(mul1*k + wave1/128), lvl1);        // Another fixed frequency, variable phase sine wave with lowered level
    leds[k].g = qsub8(sin8(mul2*k + wave2/128), lvl2);        // A fixed frequency, variable phase sine wave with lowered level
    leds[k].b = qsub8(sin8(mul3*k + wave3/128), lvl3);        // A fixed frequency, variable phase sine wave with lowered level
  }
} // three_sin()


void ThreeSin::ChangeMe() {
  uint8_t secondHand = (millis() / 1000) % 30;                // Increase this and add more options below if you want a longer demo.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.


  if(lastSecond != secondHand) {                              // You can change variables, but remember to set them back in the next demo, or they will stay as is.
    lastSecond = secondHand;
    switch(secondHand) {
      case 0: thisdelay = 25; mul1 = 20; mul2 = 25; mul3 = 22; lvl1 = 80; lvl2 = 80; lvl3 = 80; inc1 = 1; inc2 = 1; inc3 = -1; break;
      case 10: mul1 = 5; mul2 = 8; mul3 = 7; break;
      case 20: thisdelay = 40; lvl1 = 220; lvl2 = 220; lvl3 = 220; break;
      case 30: break;
    }
  }
} // ChangeMe()
