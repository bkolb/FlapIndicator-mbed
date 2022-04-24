#pragma once

#include <cstdint>

#include "StateTypes.h"

struct RavVal2LedThreshold {
	uint16_t LL_VAL;
	uint16_t L5_VAL;
	uint16_t L4_VAL;
	uint16_t L3_VAL;
	uint16_t L2_VAL;
	uint16_t L1_VAL;
	uint16_t OFFSET;
	uint16_t OFFSET_L;
};

class AbstractFlapPosReader
{
	const RavVal2LedThreshold thresholds;

  protected:
	auto rawToState(uint16_t rawVal) const;

  public:
	explicit AbstractFlapPosReader(const RavVal2LedThreshold &thresholds);
	virtual uint16_t readRawVal() const = 0;

	flapState_t currentState() const;
};