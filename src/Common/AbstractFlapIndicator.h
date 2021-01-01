#pragma once

#include "StateTypes.h"

class AbstractFlapIndicator {

    public:
        virtual void updateState(flapState_t newState) = 0;

};