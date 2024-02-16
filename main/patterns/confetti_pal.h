#ifndef EXPLORATORE_CONFETTI_PAL_H
#define EXPLORATORE_CONFETTI_PAL_H

#include "pattern.h"

class ConfettiPal : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
 private:
	void ChangeMe();
	void confetti_pal();
};

#endif
