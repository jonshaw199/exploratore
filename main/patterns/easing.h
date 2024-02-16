#ifndef EXPLORATORE_EASING_H
#define EXPLORATORE_EASING_H

#include "pattern.h"

class Easing : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void ease();
};

#endif
