#ifndef EXPLORATORE_RAINBOW_BEAT_H
#define EXPLORATORE_RAINBOW_BEAT_H

#include "pattern.h"

class RainbowBeat : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void rainbow_beat();
};

#endif
