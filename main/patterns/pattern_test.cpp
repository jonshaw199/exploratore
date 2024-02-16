#include "pattern_test.h"

static const char *TAG = "pattern_test";

void PatternTest::loop()
{
    // leds[0] = CRGB::White;
    fill_solid(leds, num_leds, CRGB::AliceBlue);
    FastLED.show();
    ESP_LOGI(TAG, "On");
    vTaskDelay(500);
    fill_solid(leds, num_leds, CRGB::Red);
    // leds[0] = CRGB::Black;
    FastLED.show();
    ESP_LOGI(TAG, "Off");
    vTaskDelay(500);
}
