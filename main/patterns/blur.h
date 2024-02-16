#ifndef EXPLORATORE_BLUR_H
#define EXPLORATORE_BLUR_H

#include "pattern.h"

class Blur : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
};

#endif
