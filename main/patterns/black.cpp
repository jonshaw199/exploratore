/* black
 *
 * By: Andrew Tuline
 * 
 * Date: July, 2015
 * 
 * Please, just turn off the damn colours while I do some more programming.
 *
 */


#include "FastLED.h"                                          // FastLED library. Please use the latest development version.
#include "black.h"

void Black::loop() {     

  fill_solid(leds, num_leds, CRGB::Black);                    // Just to be sure, let's really make it BLACK.
  FastLED.show();                         // Power managed display
  
} // loop()
