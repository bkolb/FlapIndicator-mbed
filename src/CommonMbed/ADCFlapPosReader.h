#pragma once

#include "AbstractFlapPosReader.h"

#include "AnalogIn.h"
#include "PinNames.h"

class ADCFlapPosReader : public AbstractFlapPosReader {
    mbed::AnalogIn* input;

    public:
        explicit ADCFlapPosReader(PinName adcPin);
        ~ADCFlapPosReader();
    
    protected:
        uint16_t readRawVal() const override;
};