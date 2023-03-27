#include "AbstractFlapPosReader.h"
#include <cstdint>
//#include <cstdio>


AbstractFlapPosReader::AbstractFlapPosReader(const RavVal2LedThreshold &thresholds) : thresholds(thresholds) {}

auto AbstractFlapPosReader::rawToState(uint16_t rawVal) const
{
	flapState_t measuredState {};
	//printf("\r    ==> %u", rawVal);
	// smaller values => slower speeds / higher flaps
	if (rawVal <= thresholds.LL_MAX) {
		measuredState.ledL = true;
	} else if (rawVal <= thresholds.L5_MIN) {
		measuredState.ledL = true;
		measuredState.led5 = true;
	} else if (rawVal <= thresholds.L5_MAX) {
		measuredState.led5 = true;
	} else if (rawVal <= thresholds.L4_MIN) {
		measuredState.led5 = true;
		measuredState.led4 = true;
	} else if (rawVal <= thresholds.L4_MAX) {
		measuredState.led4 = true;
	} else if (rawVal <= thresholds.L3_MIN) {
		measuredState.led4 = true;
		measuredState.led3 = true;
	} else if (rawVal <= thresholds.L3_MAX) {
		measuredState.led3 = true;
	} else if (rawVal <= thresholds.L2_MIN) {
		measuredState.led3 = true;
		measuredState.led2 = true;
	} else if (rawVal <= thresholds.L2_MAX) {
		measuredState.led2 = true;
	} else if (rawVal <= thresholds.L1_MIN) {
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