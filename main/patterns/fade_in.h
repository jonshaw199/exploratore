#ifndef EXPLORATORE_FADE_IN_H
#define EXPLORATORE_FADE_IN_H

#include "pattern.h"

class FadeIn : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void fade_in();
};

#endif
