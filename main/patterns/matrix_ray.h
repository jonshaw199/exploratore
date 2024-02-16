#ifndef EXPLORATORE_MATRIX_RAY_H
#define EXPLORATORE_MATRIX_RAY_H

#include "pattern.h"

class MatrixRay : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void matrix_ray(uint8_t colorIndex);
};

#endif
