#pragma once

#include "AbstractStateExchange.h"

#include "BufferedSerial.h"
#include "PinNames.h"

class UARTStateExchange : public AbstractStateExchange {
    mbed::BufferedSerial* uart;

    public:
        UARTStateExchange(PinName tx, PinName rx);
        ~UARTStateExchange();

        void sendString(Msg msg) override;
};