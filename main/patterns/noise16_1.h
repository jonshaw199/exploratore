#ifndef EXPLORATORE_NOISE16_1_H
#define EXPLORATORE_NOISE16_1_H

#include "pattern.h"

class Noise161 : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void noise16_1();
};

#endif
