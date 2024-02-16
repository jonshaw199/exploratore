#ifndef EXPLORATORE_RIPPLES_H
#define EXPLORATORE_RIPPLES_H

#include "pattern.h"

class Ripples : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void do_ripples();
	void SetupMySimilar4Palette();
};

#endif
