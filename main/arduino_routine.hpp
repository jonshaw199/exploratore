#ifndef ARDUINO_ROUTINE_H_
#define ARDUINO_ROUTINE_H_

#include "event_listener.hpp"
#include <string>
#include <M5StickCPlus.h>

class ArduinoRoutine : public EventListener {
public:
  ArduinoRoutine(std::string name = "", TFT_eSprite* sprite = nullptr);
  ~ArduinoRoutine() = default;
  virtual void setup();
  virtual void loop();
  virtual void handle_event(int event) override;
  std::string get_name();

protected:
    TFT_eSprite* sprite;

private:
    std::string name;
};

#endif // ARDUINO_ROUTINE_H_
