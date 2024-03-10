#include "arduino_routine.hpp"

ArduinoRoutine::ArduinoRoutine(std::string name, TFT_eSprite* sprite) : sprite(sprite), name(name) {}

void ArduinoRoutine::setup() {}

void ArduinoRoutine::loop() {}

void ArduinoRoutine::handle_event(int event) {}

std::string ArduinoRoutine::get_name() {
	return name;
}
