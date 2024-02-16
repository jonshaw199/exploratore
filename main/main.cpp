#include "nvs_flash.h"
#include "Arduino.h"
#include "esp_system.h"
#include <M5StickCPlus.h>
#include <FastLED.h>
#include <mutex>

#define NUM_LEDS 60
#define LED_PIN 26

#include "black.h"
#include "pattern_test.h"
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

#define NUM_PATTERNS 33

const char *TAG = "main";

CRGB leds[NUM_LEDS];
uint8_t pattern_idx;
std::mutex pattern_idx_mutex;
Pattern *patterns[NUM_PATTERNS] = {
  new Black(leds, NUM_LEDS),
	new PatternTest(leds, NUM_LEDS),
	new Confetti(leds, NUM_LEDS),
	new Beatwave(leds, NUM_LEDS),
	new Blendwave(leds, NUM_LEDS),
	new Blur(leds, NUM_LEDS),
	new ConfettiPal(leds, NUM_LEDS),
	new DotBeat(leds, NUM_LEDS),
	new Easing(leds, NUM_LEDS),
	new FadeIn(leds, NUM_LEDS),
	new Inoise8Fire(leds, NUM_LEDS),
	new Inoise8Mover(leds, NUM_LEDS),
	new Inoise8Pal(leds, NUM_LEDS),
	new JugglePal(leds, NUM_LEDS),
	new Lightnings(leds, NUM_LEDS),
	new MatrixPal(leds, NUM_LEDS),
	new MatrixRay(leds, NUM_LEDS),
	new Noise161(leds, NUM_LEDS),
	new Noise162(leds, NUM_LEDS),
	new Noise163(leds, NUM_LEDS),
	new OneSinePal(leds, NUM_LEDS),
	new PaletteCrossfade(leds, NUM_LEDS),
	new Plasma(leds, NUM_LEDS),
	new RainbowBeat(leds, NUM_LEDS),
	new RainbowMarch(leds, NUM_LEDS),
	new RainbowPal(leds, NUM_LEDS),
	new Ripples(leds, NUM_LEDS),
    new Sawtooth(leds, NUM_LEDS),
    new Serendipitous(leds, NUM_LEDS),
    new Sinelon(leds, NUM_LEDS),
    new ThreeSin(leds, NUM_LEDS),
    new ThreeSinPal(leds, NUM_LEDS),
    new TwoSinPal(leds, NUM_LEDS)
};

static void m5stickcplus_setup()
{
    M5.begin();
    M5.Lcd.fillScreen(WHITE);
}

static void m5stickcplus_loop(void *pv_parameters)
{
    while (1)
    {
        M5.update();

        if (M5.BtnA.wasReleased())
        {
            M5.Lcd.print('A');
            ESP_LOGI(TAG, "A");

        	pattern_idx_mutex.lock();
        	pattern_idx = (pattern_idx + 1) % NUM_PATTERNS;
            ESP_LOGI(TAG, "Pattern #%d", pattern_idx);
            patterns[pattern_idx]->setup();
        	pattern_idx_mutex.unlock();
        }
        else if (M5.BtnB.wasReleased())
        {
            M5.Lcd.print('B');
            ESP_LOGI(TAG, "B");
        }
        else if (M5.BtnB.wasReleasefor(700))
        {
            M5.Lcd.fillScreen(BLACK);
            M5.Lcd.setCursor(0, 0);
            ESP_LOGI(TAG, "C");
        }

        vTaskDelay(100);
    }
}

static void led_setup()
{
    FastLED.addLeds<WS2811, LED_PIN>(leds, NUM_LEDS);
    const std::lock_guard<std::mutex> lock(pattern_idx_mutex);
    patterns[pattern_idx]->setup();
}

static void led_loop(void *pv_parameters)
{
    while (1)
    {
        pattern_idx_mutex.lock();
        patterns[pattern_idx]->loop();
        pattern_idx_mutex.unlock();
        vTaskDelay(5);
    }
}

extern "C" void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    initArduino();
    m5stickcplus_setup();
    xTaskCreatePinnedToCore(m5stickcplus_loop, "m5stickcplus_loop", 2048, NULL, 3, NULL, 0);
    led_setup();
    xTaskCreatePinnedToCore(led_loop, "led_loop", 2048, NULL, 3, NULL, 1);
};
