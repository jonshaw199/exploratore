/*
 * Ripples
 * 
 * Originally by: Reko Meriö
 * 
 * Highly modified by: Andrew Tuline
 * 
 * Date: February, 2019
 * 
 * A ripple routine that supports simultaneous ripples via a structure.
 * 
 * 
 */



#include "FastLED.h"
#include "ripples.h"

#define maxRipples 6                                                            // Min is 2 and value has to be divisible by two because each ripple has a left and right component. This cuts down on bouncing code.

//----------------- Ripple structure definition ----------------------------------------------------------------

struct ripple {                                                                 // Reko Meriö's structures
// Local definitions
// Persistent local variables
// Temporary local variables
  uint8_t brightness;                                   // 0 to 255
  int8_t color;                                         // 0 to 255
  int16_t pos;                                           // -1 to num_leds  (up to 127 LED's)
  int8_t velocity;                                      // 1 or -1
  uint8_t life;                                         // 0 to 20
  uint8_t maxLife;                                      // 10. If it's too long, it just goes on and on. . .
  uint8_t fade;                                         // 192
  bool exist;                                           // 0 to 1

  
  void Move(uint16_t num_leds) {
    
    pos += velocity;
    life++;
    
    if (pos > num_leds - 1) {                           // Bounce back from far end.
      velocity *= -1;
      pos = num_leds - 1;
    }
    
    if (pos < 0) {                                      // Bounce back from 0.
      velocity *= -1;
      pos = 0;
    }

    brightness = scale8(brightness, fade);              // Adjust brightness accordingly to strip length

    if (life > maxLife) exist = false;                  // Kill it once it's expired.
    
  } // Move()


  
  void Init(uint8_t Fade, uint8_t MaxLife, uint16_t num_leds) {                 // Typically 216, 20
    
    pos = random8(num_leds/8, num_leds-num_leds/8);     // Avoid spawning too close to edge.
    velocity = 1;                                       // -1 or 1
    life = 0;                                           // 0 to Maxlife
    maxLife = MaxLife;                                  // 10 called
    exist = true;                                       // 0, 1
    brightness = 255;                                   // 0 to 255
    color = millis();                                   // hue;
    fade = Fade;                                        // 192 called
    
  } // Init()
  
}; // struct ripple

namespace ripples_ns {
	uint8_t max_bright = 128;                                                       // Overall brightness definition. It can be changed on the fly.

	CRGBPalette16 currentPalette = OceanColors_p;                                   // Use palettes instead of direct CHSV or CRGB assignments
	CRGBPalette16 targetPalette = OceanColors_p;                                    // Also support smooth palette transitioning

	typedef struct ripple Ripple;

	Ripple ripples[maxRipples];
};

using namespace ripples_ns;

void Ripples::loop() {

  EVERY_N_MILLISECONDS(50) {                                                      // Smooth palette transitioning runs continuously.
    uint8_t maxChanges = 24; 
      nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);  
  }

  EVERY_N_SECONDS(5) {
    SetupMySimilar4Palette();                                                     // Change palette colours every 5 seconds.
  }

  EVERY_N_MILLIS(50) {                                                            // Sets the original delay time.
    do_ripples();                                                                   // Run the ripple routine.
  }

  FastLED.show();                                                                 // Power managed display of LED's.
  
} // loop()

void Ripples::do_ripples() {

  for (int i = 0; i < maxRipples; i += 2) {                                       // Check to see if ripple has expired, and if so, create a new one.
    if (random8() > 224 && !ripples[i].exist) {                                   // Randomly create a new ripple if this one has expired.
      ripples[i].Init(192, 10, num_leds);                                                   // Initialize the ripple array with Fade and MaxLife values.
      ripples[i + 1] = ripples[i];                                                // Everything except velocity is the same for the ripple's other half. Position starts out the same for both halves.
      ripples[i + 1].velocity *= -1;                                              // We want the other half of the ripple to go opposite direction.
    }
  }
  
  for (int i = 0; i < maxRipples; i++) {                                          // Move the ripple if it exists
    if (ripples[i].exist) {
      leds[ripples[i].pos] = ColorFromPalette(currentPalette, ripples[i].color, ripples[i].brightness, LINEARBLEND);
      ripples[i].Move(num_leds);
    }
  }

  fadeToBlackBy(leds, num_leds, 160);
  
} // rippless()

void Ripples::SetupMySimilar4Palette() {                                                   // Create a palette with colours close to each other.

  uint8_t thishue = random8();
  
  targetPalette = CRGBPalette16(CHSV(thishue+random8(32), 255, random8(128,255)),
                                CHSV(thishue+random8(32), 255, random8(192,255)),
                                CHSV(thishue+random8(32), 192, random8(192,255)),
                                CHSV(thishue+random8(32), 255, random8(128,255)));
                                
} // SetupMySimilar4Palette()
