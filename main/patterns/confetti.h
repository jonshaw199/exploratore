#ifndef EXPLORATORE_CONFETTI_H
#define EXPLORATORE_CONFETTI_H

#include "pattern.h"

class Confetti : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
  void confetti();
  void change_me();
};

#endif
