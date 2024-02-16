#ifndef EXPLORATORE_ONE_SINE_PAL_H
#define EXPLORATORE_ONE_SINE_PAL_H

#include "pattern.h"

class OneSinePal : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void one_sine_pal(uint8_t colorIndex);
};

#endif
