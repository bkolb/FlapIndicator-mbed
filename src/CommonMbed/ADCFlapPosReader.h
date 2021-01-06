#pragma once

#include "PinNames.h"

#include "AbstractFlapPosReader.h"
#include "AnalogIn.h"

class ADCFlapPosReader : public AbstractFlapPosReader
{
	mbed::AnalogIn *input;

  public:
	explicit ADCFlapPosReader(PinName adcPin, RavVal2LedThreshold& raw2led);
	~ADCFlapPosReader();

  protected:
	uint16_t readRawVal() const override;
};