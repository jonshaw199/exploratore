#ifndef EXPLORATORE_JUGGLE_PAL_H
#define EXPLORATORE_JUGGLE_PAL_H

#include "pattern.h"

class JugglePal : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void juggle_pal();
	void ChangeMe();
};

#endif
