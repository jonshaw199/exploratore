#ifndef EXPLORATORE_BEATWAVE_H
#define EXPLORATORE_BEATWAVE_H

#include "pattern.h"

class Beatwave : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
 private:
	void beatwave();
};

#endif
