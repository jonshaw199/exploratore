#ifndef EXPLORATORE_SAWTOOTH_H
#define EXPLORATORE_SAWTOOTH_H

#include "pattern.h"

class Sawtooth : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
    void sawtooth();
};

#endif
