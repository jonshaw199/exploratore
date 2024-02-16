#ifndef EXPLORATORE_RAINBOW_MARCH_H
#define EXPLORATORE_RAINBOW_MARCH_H

#include "pattern.h"

class RainbowMarch : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void rainbow_march(uint8_t thisdelay, uint8_t deltahue);
};

#endif
