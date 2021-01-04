#include "ADCFlapPosReader.h"
#include <cstdint>
#include <cstdio>


ADCFlapPosReader::ADCFlapPosReader(PinName adcPin):
    AbstractFlapPosReader(RavVal2LedThreshold{
        .LL_VAL     = 10000,
        .LL_L5_VAL  = 15000,
        .L5_VAL     = 20000,
        .L5_L4_VAL  = 25000,
        .L4_VAL     = 30000,
        .L4_L3_VAL  = 35000,
        .L3_VAL     = 40000,
        .L3_L2_VAL  = 45000,
        .L2_VAL     = 50000,
        .L2_L1_VAL  = 55000,
        .L1_VAL     = 60000
    }),
    input(new mbed::AnalogIn(adcPin)){

    }
        
ADCFlapPosReader::~ADCFlapPosReader() {
    delete input;
}

uint16_t ADCFlapPosReader::readRawVal() const{
    uint16_t raw = input->read_u16();
    return raw;
};
