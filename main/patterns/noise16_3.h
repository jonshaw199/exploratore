#ifndef EXPLORATORE_NOISE16_3_H
#define EXPLORATORE_NOISE16_3_H

#include "pattern.h"

class Noise163 : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void noise16_3();
};

#endif
