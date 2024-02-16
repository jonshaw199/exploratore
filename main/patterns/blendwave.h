#ifndef EXPLORATORE_BLENDWAVE_H
#define EXPLORATORE_BLENDWAVE_H

#include "pattern.h"

class Blendwave : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
};

#endif
