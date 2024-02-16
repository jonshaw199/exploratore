/* blur
 *
 * By: ????
 * 
 * Modified by: Andrew Tuline
 *
 * Date: July, 2015
 *
 * Let's try the blur function. If you look carefully at the animation, sometimes there's a smooth gradient between each LED.
 * Other times, the difference between them is quite significant. Thanks for the blur.
 *
 */

#include "FastLED.h"                                          // FastLED library.
#include "blur.h"

void Blur::loop() {
  uint8_t blurAmount = dim8_raw( beatsin8(3,64, 192) );       // A sinewave at 3 Hz with values ranging from 64 to 192.
  blur1d( leds, num_leds, blurAmount);                        // Apply some blurring to whatever's already on the strip, which will eventually go black.
  
  uint8_t  i = beatsin8(  9, 0, num_leds);
  uint8_t  j = beatsin8( 7, 0, num_leds);
  uint8_t  k = beatsin8(  5, 0, num_leds);
  
  // The color of each point shifts over time, each at a different speed.
  uint16_t ms = millis();  
  leds[(i+j)/2] = CHSV( ms / 29, 200, 255);
  leds[(j+k)/2] = CHSV( ms / 41, 200, 255);
  leds[(k+i)/2] = CHSV( ms / 73, 200, 255);
  leds[(k+i+j)/3] = CHSV( ms / 53, 200, 255);
  
  FastLED.show();
  
} // loop()
 
