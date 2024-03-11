#ifndef EVIL_REMOTE_H_
#define EVIL_REMOTE_H_

#include "arduino_routine.hpp"

class EvilRemote : public ArduinoRoutine {
public:
  EvilRemote(std::string name = "", TFT_eSprite* sprite = nullptr);
  virtual void setup() override;
  virtual void handle_event(int event) override;
private:
  void send_all_codes();
};

#endif // EVIL_REMOTE_H_
