#ifndef EXPLORATORE_INOISE8_MOVER_H
#define EXPLORATORE_INOISE8_MOVER_H

#include "pattern.h"

class Inoise8Mover : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void inoise8_mover();
};

#endif
