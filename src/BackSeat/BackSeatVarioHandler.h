#pragma once

#include "AbstractVarioHandler.h"
#include "AbstractStateExchange.h"
#include "PinNames.h"

#include "InterruptIn.h"

class BackSeatVarioHandler: public AbstractVarioHandler {

    AbstractStateExchange* comm;
    mbed::InterruptIn* varioBtn;

    public:
        BackSeatVarioHandler(AbstractStateExchange* comm, PinName varioButtonPin);
        ~BackSeatVarioHandler();

        void handleVarioButtonPressed() override;
};