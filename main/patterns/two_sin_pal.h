#ifndef EXPLORATORE_TWO_SIN_PAL_H
#define EXPLORATORE_TWO_SIN_PAL_H

#include "pattern.h"

class TwoSinPal : public Pattern
{
public:
	using Pattern::Pattern;
    virtual void setup() override;
	virtual void loop() override;
private:
    void two_sin();
    void ChangeMe();
    void resetvars();
};

#endif
