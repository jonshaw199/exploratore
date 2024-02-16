#ifndef EXPLORATORE_INOISE8_FIRE_H
#define EXPLORATORE_INOISE8_FIRE_H

#include "pattern.h"

class Inoise8Fire : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void inoise8_fire();
};

#endif
