#ifndef EXPLORATORE_RAINBOW_PAL_H
#define EXPLORATORE_RAINBOW_PAL_H

#include "pattern.h"

class RainbowPal : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void ripple();
};

#endif
