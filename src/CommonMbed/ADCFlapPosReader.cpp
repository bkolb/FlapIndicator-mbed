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

constexpr std::uint8_t NUM_AVG  = 10;

uint16_t ADCFlapPosReader::readRawVal() const{
    uint32_t raw = 0;
    for (uint8_t i=0; i<NUM_AVG; i++) {
    raw += input->read_u16();
    }

    uint16_t res = raw/NUM_AVG;
    return res;
};
