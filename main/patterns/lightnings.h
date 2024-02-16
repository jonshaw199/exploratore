#ifndef EXPLORATORE_LIGHTNINGS_H
#define EXPLORATORE_LIGHTNINGS_H

#include "pattern.h"

class Lightnings : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
};

#endif
