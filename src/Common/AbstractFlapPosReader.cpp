#include "AbstractFlapPosReader.h"

AbstractFlapPosReader::AbstractFlapPosReader(const RavVal2LedThreshold& thresholds): thresholds(thresholds){}

auto AbstractFlapPosReader::rawToState(uint16_t rawVal) const {
    flapState_t measuredState{};
    if(rawVal<thresholds.L1_VAL) {
        measuredState.led1=true;
    } else if (rawVal<thresholds.L1_L2_VAL) {
        measuredState.led1=true;
        measuredState.led2=true;
    } else if(rawVal<thresholds.L2_VAL) {
        measuredState.led2=true;
    } else if (rawVal<thresholds.L2_L3_VAL) {
        measuredState.led2=true;
        measuredState.led3=true;
    } if(rawVal<thresholds.L3_VAL) {
        measuredState.led3=true;
    } else if (rawVal<thresholds.L3_L4_VAL) {
        measuredState.led3=true;
        measuredState.led4=true;
    } if(rawVal<thresholds.L4_VAL) {
        measuredState.led4=true;
    } else if (rawVal<thresholds.L4_L5_VAL) {
        measuredState.led4=true;
        measuredState.led5=true;
    } if(rawVal<thresholds.L5_VAL) {
        measuredState.led5=true;
    } else if (rawVal<thresholds.L5_LL_VAL) {
        measuredState.led5=true;
        measuredState.ledL=true;
    } else {
        measuredState.ledL=true;
    }
    return measuredState;
}

flapState_t AbstractFlapPosReader::currentState() const {
    return rawToState(readRawVal());
}