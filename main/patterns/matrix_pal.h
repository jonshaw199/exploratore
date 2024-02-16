#ifndef EXPLORATORE_MATRIX_PAL_H
#define EXPLORATORE_MATRIX_PAL_H

#include "pattern.h"

class MatrixPal : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void matrix();
	void ChangeMe();
};

#endif
