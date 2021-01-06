#include "ADCFlapPosReader.h"
#include <cstdint>
#include <cstdio>

ADCFlapPosReader::ADCFlapPosReader(PinName adcPin, RavVal2LedThreshold& raw2led)
	: AbstractFlapPosReader(raw2led),
	  input(new mbed::AnalogIn(adcPin))
{
}

ADCFlapPosReader::~ADCFlapPosReader()
{
	delete input;
}

uint16_t ADCFlapPosReader::readRawVal() const
{
	uint16_t raw = input->read_u16();
	return raw;
};
