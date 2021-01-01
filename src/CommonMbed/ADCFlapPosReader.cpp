#include "ADCFlapPosReader.h"


ADCFlapPosReader::ADCFlapPosReader(PinName adcPin):
    AbstractFlapPosReader(RavVal2LedThreshold{
        .L1_VAL     = 100,
        .L1_L2_VAL  = 120,
        .L2_VAL     = 200,
        .L2_L3_VAL  = 220,
        .L3_VAL     = 300,
        .L3_L4_VAL  = 320,
        .L4_VAL     = 400,
        .L4_L5_VAL  = 420,
        .L5_VAL     = 500,
        .L5_LL_VAL  = 520,
        .LL_VAL     = 600
    }),
    input(new mbed::AnalogIn(adcPin)){

    }
        
ADCFlapPosReader::~ADCFlapPosReader() {
    delete input;
}

uint16_t ADCFlapPosReader::readRawVal() const{
    return input->read_u16();
};
