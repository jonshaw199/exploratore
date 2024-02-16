#ifndef EXPLORATORE_THREE_SIN_PAL_H
#define EXPLORATORE_THREE_SIN_PAL_H

#include "pattern.h"

class ThreeSinPal : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
    void three_sin();
    void ChangeMe();
};

#endif
