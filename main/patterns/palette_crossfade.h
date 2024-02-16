#ifndef EXPLORATORE_PALETTE_CROSSFADE_H
#define EXPLORATORE_PALETTE_CROSSFADE_H

#include "pattern.h"

class PaletteCrossfade : public Pattern
{
public:
	using Pattern::Pattern;
	virtual void loop() override;
private:
	void FillLEDsFromPaletteColors(uint8_t colorIndex);
	void ChangePalettePeriodically();
};

#endif
