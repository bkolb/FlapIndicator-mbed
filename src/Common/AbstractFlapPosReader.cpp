#include "AbstractFlapPosReader.h"
#include <cstdint>

AbstractFlapPosReader::AbstractFlapPosReader(const RavVal2LedThreshold &thresholds) : thresholds(thresholds) {}

auto AbstractFlapPosReader::rawToState(uint16_t rawVal) const
{
	flapState_t measuredState {};
	// smaller values => slower speeds / higher flaps
	if (rawVal <= thresholds.LL_VAL) {
		measuredState.ledL = true;
	} else if (rawVal <= thresholds.LL_L5_VAL) {
		measuredState.ledL = true;
		measuredState.led5 = true;
	} else if (rawVal <= thresholds.L5_VAL) {
		measuredState.led5 = true;
	} else if (rawVal <= thresholds.L5_L4_VAL) {
		measuredState.led5 = true;
		measuredState.led4 = true;
	} else if (rawVal <= thresholds.L4_VAL) {
		measuredState.led4 = true;
	} else if (rawVal <= thresholds.L4_L3_VAL) {
		measuredState.led4 = true;
		measuredState.led3 = true;
	} else if (rawVal <= thresholds.L3_VAL) {
		measuredState.led3 = true;
	} else if (rawVal <= thresholds.L3_L2_VAL) {
		measuredState.led3 = true;
		measuredState.led2 = true;
	} else if (rawVal <= thresholds.L2_VAL) {
		measuredState.led2 = true;
	} else if (rawVal <= thresholds.L2_L1_VAL) {
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