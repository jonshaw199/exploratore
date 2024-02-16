#ifndef EXPLORATORE_DOT_BEAT_H
#define EXPLORATORE_DOT_BEAT_H

#include "pattern.h"

class DotBeat : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
};

#endif
