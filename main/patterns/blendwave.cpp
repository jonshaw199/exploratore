/* blendwave
 *  
 *  By: Andrew Tuline
 *  
 *  Date: October, 2015
 *  
 *  This uses beats, blend and the fill gradient functions to blend a couple of waves together. Again, try making changes to this and see how it looks.
 *  
 */

#include "FastLED.h"                                          // FastLED library.
#include "blendwave.h"

namespace blendwave_ns {
  CRGB clr1;
  CRGB clr2;
  uint8_t speed;
  uint8_t loc1;
  uint8_t loc2;
  uint8_t ran1;
  uint8_t ran2;
};

using namespace blendwave_ns;

void Blendwave::loop(){ 
  speed = beatsin8(6,0,255);

  clr1 = blend(CHSV(beatsin8(3,0,255),255,255), CHSV(beatsin8(4,0,255),255,255), speed);
  clr2 = blend(CHSV(beatsin8(4,0,255),255,255), CHSV(beatsin8(3,0,255),255,255), speed);

  loc1 = beatsin8(10,0,num_leds-1);
  
  fill_gradient_RGB(leds, 0, clr2, loc1, clr1);
  fill_gradient_RGB(leds, loc1, clr2, num_leds-1, clr1);

  FastLED.show();
  
} // loop()
