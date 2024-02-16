#ifndef EXPLORATORE_PATTERN_TEST_H
#define EXPLORATORE_PATTERN_TEST_H

#include "pattern.h"

class PatternTest : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
};

#endif
