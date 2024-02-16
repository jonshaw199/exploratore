#ifndef EXPLORATORE_INOISE8_PAL_H
#define EXPLORATORE_INOISE8_PAL_H

#include "pattern.h"

class Inoise8Pal : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void inoise8_pal();
};

#endif
