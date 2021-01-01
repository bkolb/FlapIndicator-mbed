#pragma once

#include "AbstractStateExchange.h"

#include "BufferedSerial.h"
#include "PinNames.h"


class UARTStateExchange : public AbstractStateExchange {
    mbed::BufferedSerial* uart;

    protected:
        void sendString(Msg msg) override;

    public:
        UARTStateExchange(PinName tx, PinName rx);
        ~UARTStateExchange();
};