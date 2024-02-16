#ifndef EXPLORATORE_SERENDIPITOUS_H
#define EXPLORATORE_SERENDIPITOUS_H

#include "pattern.h"

class Serendipitous : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
    void serendipitous();
};

#endif
