#include "nvs_flash.h"
#include "Arduino.h"
#include "esp_system.h"
#include <M5StickCPlus.h>
#include <mutex>
#include "patterns.hpp"
#include "imu_wake_on_motion.h"

#define NUM_MODES 1

#define EVENT_BTN_A 1
#define EVENT_BTN_B 2
#define EVENT_BTN_B_HOLD 3

const char *TAG = "main";

uint8_t mode_idx;
std::mutex mode_idx_mutex;

TFT_eSprite screen_sprite = TFT_eSprite(&M5.Lcd);

ArduinoRoutine *modes[NUM_MODES] = {
    new Patterns("Patterns", &screen_sprite)
};

IMUWakeOnMotion m5stickcplus_wake;


static void m5stickcplus_setup()
{
	M5.begin();
	//M5.Lcd.setRotation(3);
	//M5.Lcd.fillScreen(BLACK);
	//M5.Lcd.setTextSize(2);
	screen_sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
	screen_sprite.drawString(modes[mode_idx]->get_name().c_str(), 2, 2);
	screen_sprite.drawLine(0, 15, M5.Lcd.width(), 15, WHITE);
	screen_sprite.pushSprite(0, 0);
}


void m5stickcplus_loop(void *pv_parameters)
{
    while (1)
    {
        M5.update();

        if (M5.BtnA.wasReleased()) {
            ESP_LOGI(TAG, "A");
        } else if (M5.BtnB.wasReleased()) {
            ESP_LOGI(TAG, "B");
            mode_idx_mutex.lock();
            modes[mode_idx]->handle_event(EVENT_BTN_B);
            mode_idx_mutex.unlock();
        } else if (M5.BtnB.wasReleasefor(700)) {
            ESP_LOGI(TAG, "B Hold");
            mode_idx_mutex.lock();
            modes[mode_idx]->handle_event(EVENT_BTN_B_HOLD);
            mode_idx = (mode_idx + 1) % NUM_MODES;
            modes[mode_idx]->setup();
            mode_idx_mutex.unlock();
        }
	
	screen_sprite.pushSprite(0, 0);

        vTaskDelay(5);
    }
}

static void m5stickcplus_wake_loop(void *pv_parameters)
{
   m5stickcplus_wake.setup();
}

static void mode_setup()
{
    modes[mode_idx]->setup();
}

static void mode_loop(void *pv_parameters)
{
    while (1) {
        mode_idx_mutex.lock();
        modes[mode_idx]->loop();
        mode_idx_mutex.unlock();
        vTaskDelay(5);
    }
}

extern "C" void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    initArduino();
    m5stickcplus_setup();
    mode_setup();

    xTaskCreatePinnedToCore(m5stickcplus_loop, "m5stickcplus_loop", 2048, NULL, 3, NULL, 0);
    //xTaskCreatePinnedToCore(m5stickcplus_wake_loop, "m5stickcplus_wake_loop", 2048, NULL, 3, NULL, 0);
    xTaskCreatePinnedToCore(mode_loop, "mode_loop", 2048, NULL, 3, NULL, 1);
};
