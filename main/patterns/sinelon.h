#ifndef EXPLORATORE_SINELON_H
#define EXPLORATORE_SINELON_H

#include "pattern.h"

class Sinelon : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
    void sinelon();
};

#endif
