#ifndef EXPLORATORE_NOISE16_2_H
#define EXPLORATORE_NOISE16_2_H

#include "pattern.h"

class Noise162 : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void noise16_2();
};

#endif
