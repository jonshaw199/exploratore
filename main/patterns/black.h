#ifndef EXPLORATORE_BLACK_H
#define EXPLORATORE_BLACK_H

#include "pattern.h"

class Black : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
};

#endif
