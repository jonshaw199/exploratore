#ifndef PATTERNS_H_
#define PATTERNS_H_

#include "arduino_routine.hpp"

class Patterns : public ArduinoRoutine {
public:
  Patterns(std::string name = "", TFT_eSprite* sprite = nullptr);
  void setup() override;
  void loop() override;
  void handle_event(int event) override;

private:
  void show_pattern_name();
};

#endif // PATTERNS_H_
