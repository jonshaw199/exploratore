#include "patterns.hpp"

#include <mutex>
#include <FastLED.h>
#include <mutex>
#include <M5StickCPlus.h>

#include "black.h"
#include "pattern.h"
#include "confetti.h"
#include "beatwave.h"
#include "blendwave.h"
#include "blur.h"
#include "confetti_pal.h"
#include "dot_beat.h"
#include "easing.h"
#include "fade_in.h"
#include "inoise8_fire.h"
#include "inoise8_mover.h"
#include "inoise8_pal.h"
#include "juggle_pal.h"
#include "lightnings.h"
#include "matrix_pal.h"
#include "matrix_ray.h"
#include "noise16_1.h"
#include "noise16_2.h"
#include "noise16_3.h"
#include "one_sine_pal.h"
#include "palette_crossfade.h"
#include "plasma.h"
#include "rainbow_beat.h"
#include "rainbow_march.h"
#include "rainbow_pal.h"
#include "ripples.h"
#include "sawtooth.h"
#include "serendipitous.h"
#include "sinelon.h"
#include "three_sin.h"
#include "three_sin_pal.h"
#include "two_sin_pal.h"
#include "imu_wake_on_motion.h"
#include "arduino_routine.hpp"

#define NUM_LEDS 60
#define LED_PIN 26
#define NUM_PATTERNS 32

#define EVENT_NEXT_PATTERN 1

static const char *TAG = "Patterns";

CRGB leds[NUM_LEDS];
uint8_t pattern_idx;
std::mutex pattern_idx_mutex;
Pattern *patterns[NUM_PATTERNS] = {
    new Black(leds, NUM_LEDS, "Black"),
    new Confetti(leds, NUM_LEDS, "Confetti"),
    new Beatwave(leds, NUM_LEDS, "Beatwave"),
    new Blendwave(leds, NUM_LEDS, "Blendwave"),
    new Blur(leds, NUM_LEDS, "Blur"),
    new ConfettiPal(leds, NUM_LEDS, "Confetti Palette"),
    new DotBeat(leds, NUM_LEDS, "Dotbeat"),
    new Easing(leds, NUM_LEDS, "Easing"),
    new FadeIn(leds, NUM_LEDS, "Fade In"),
    new Inoise8Fire(leds, NUM_LEDS, "Noise Fire"),
    new Inoise8Mover(leds, NUM_LEDS, "Noise Mover"),
    new Inoise8Pal(leds, NUM_LEDS, "Noise Palette"),
    new JugglePal(leds, NUM_LEDS, "Juggle Palette"),
    new Lightnings(leds, NUM_LEDS, "Lightnings"),
    new MatrixPal(leds, NUM_LEDS, "Matrix Palette"),
    new MatrixRay(leds, NUM_LEDS, "Matrix Ray"),
    new Noise161(leds, NUM_LEDS, "Noise 161"),
    new Noise162(leds, NUM_LEDS, "Noise 162"),
    new Noise163(leds, NUM_LEDS, "Noise 163"),
    new OneSinePal(leds, NUM_LEDS, "One Sine Palette"),
    new PaletteCrossfade(leds, NUM_LEDS, "Palette Crossfade"),
    new Plasma(leds, NUM_LEDS, "Plasma"),
    new RainbowBeat(leds, NUM_LEDS, "Rainbow Beat"),
    new RainbowMarch(leds, NUM_LEDS, "Rainbow March"),
    new RainbowPal(leds, NUM_LEDS, "Rainbow Palette"),
    new Ripples(leds, NUM_LEDS, "Ripples"),
    new Sawtooth(leds, NUM_LEDS, "Sawtooth"),
    new Serendipitous(leds, NUM_LEDS, "Serendipitous"),
    new Sinelon(leds, NUM_LEDS, "Sinelon"),
    new ThreeSin(leds, NUM_LEDS, "Three Sine"),
    new ThreeSinPal(leds, NUM_LEDS, "Three Sine Palette"),
    new TwoSinPal(leds, NUM_LEDS, "Two Sine")
};

Patterns::Patterns(std::string name, TFT_eSprite* sprite) : ArduinoRoutine(name, sprite) {}

void Patterns::show_pattern_name() {
    if (this->sprite) {
        this->sprite->fillRect(0, this->sprite->height() / 2 - 25, this->sprite->width(), 50, BLACK);
        this->sprite->drawString(patterns[pattern_idx]->get_name().c_str(), 2, sprite->height() / 2);
    }
}

void Patterns::setup() {
    FastLED.addLeds<WS2811, LED_PIN>(leds, NUM_LEDS);
    const std::lock_guard<std::mutex> lock(pattern_idx_mutex);
    patterns[pattern_idx]->setup();
    show_pattern_name();
}

void Patterns::loop() {
    patterns[pattern_idx]->loop();
}

void Patterns::handle_event(int event) {
  switch (event) {
    case EVENT_NEXT_PATTERN:
        pattern_idx = (pattern_idx + 1) % NUM_PATTERNS;
        patterns[pattern_idx]->setup();
	show_pattern_name();
        ESP_LOGI(TAG, "Changed pattern to %s", patterns[pattern_idx]->get_name().c_str());
        break;
  }
}

