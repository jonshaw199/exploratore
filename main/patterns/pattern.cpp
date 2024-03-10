#include "pattern.h"
#include <sys/time.h>

static const char *TAG = "pattern";

Pattern::Pattern(CRGB *leds, uint16_t num_leds, std::string name) : ArduinoRoutine(name), leds(leds), num_leds(num_leds) {}

void Pattern::setup() {}

void Pattern::loop() {}

uint64_t Pattern::micros() {
	struct timeval tv_now;
	gettimeofday(&tv_now, NULL);
	return (uint64_t)tv_now.tv_sec * 1000000L + (uint64_t)tv_now.tv_usec;
}
