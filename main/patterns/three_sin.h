#ifndef EXPLORATORE_THREE_SIN_H
#define EXPLORATORE_THREE_SIN_H

#include "pattern.h"

class ThreeSin : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
    void three_sin();
    void ChangeMe();
};

#endif
