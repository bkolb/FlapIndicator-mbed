#include "AbstractFlapPosReader.h"
#include <cstdint>
//#include <cstdio>


AbstractFlapPosReader::AbstractFlapPosReader(const RavVal2LedThreshold &thresholds) : thresholds(thresholds) {}

auto AbstractFlapPosReader::rawToState(uint16_t rawVal) const
{
	uint16_t OFFSET = thresholds.OFFSET;
	uint16_t OFFSET_L = thresholds.OFFSET_L;
	flapState_t measuredState {};
	// printf("\r    ==> %u", rawVal);
	// smaller values => slower speeds / higher flaps
	if (rawVal <= thresholds.L5_VAL-OFFSET_L) {
		measuredState.ledL = true;
	} else if (rawVal <= thresholds.L5_VAL-OFFSET) {
		measuredState.ledL = true;
		measuredState.led5 = true;
	} else if (rawVal <= thresholds.L5_VAL+OFFSET) {
		measuredState.led5 = true;
	} else if (rawVal <= thresholds.L4_VAL-OFFSET) {
		measuredState.led5 = true;
		measuredState.led4 = true;
	} else if (rawVal <= thresholds.L4_VAL+OFFSET) {
		measuredState.led4 = true;
	} else if (rawVal <= thresholds.L3_VAL-OFFSET) {
		measuredState.led4 = true;
		measuredState.led3 = true;
	} else if (rawVal <= thresholds.L3_VAL+OFFSET) {
		measuredState.led3 = true;
	} else if (rawVal <= thresholds.L2_VAL-OFFSET) {
		measuredState.led3 = true;
		measuredState.led2 = true;
	} else if (rawVal <= thresholds.L2_VAL+OFFSET) {
		measuredState.led2 = true;
	} else if (rawVal <= thresholds.L1_VAL-OFFSET) {
		measuredState.led2 = true;
		measuredState.led1 = true;
	} else {
		measuredState.led1 = true;
	}

	return measuredState;
}

flapState_t AbstractFlapPosReader::currentState() const
{
	constexpr uint8_t numInt = 5;
	uint32_t integrated		 = readRawVal();
	for (uint8_t i = 0; i < numInt - 1; i++) {
		integrated += readRawVal();
	}
	uint16_t raw = integrated / numInt;
	return rawToState(raw);
}