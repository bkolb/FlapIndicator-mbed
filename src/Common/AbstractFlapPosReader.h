#pragma once

#include <cstdint>

#include "StateTypes.h"

struct RavVal2LedThreshold {
	uint16_t LL_MAX;
	uint16_t L5_MIN;
	uint16_t L5_MAX;
	uint16_t L4_MIN;
	uint16_t L4_MAX;
	uint16_t L3_MIN;
	uint16_t L3_MAX;
	uint16_t L2_MIN;
	uint16_t L2_MAX;
	uint16_t L1_MIN;
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