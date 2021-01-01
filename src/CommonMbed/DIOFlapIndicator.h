#pragma once

#include "AbstractFlapIndicator.h"

#include "DigitalOut.h"
#include "StateTypes.h"

struct LedMapping {
    mbed::DigitalOut led1;
    mbed::DigitalOut led2;
    mbed::DigitalOut led3;
    mbed::DigitalOut led4;
    mbed::DigitalOut led5;
    mbed::DigitalOut ledL;
};


class DIOFlapIndicator : public AbstractFlapIndicator {

    LedMapping* leds;

    public:
        explicit DIOFlapIndicator(LedMapping* leds);

        void updateState(flapState_t newState) override;

};