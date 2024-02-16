#ifndef EXPLORATORE_PLASMA_H
#define EXPLORATORE_PLASMA_H

#include "pattern.h"

class Plasma : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void plasma();
};

#endif
