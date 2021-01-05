#pragma once

#include "AbstractStateExchange.h"

#include "BufferedSerial.h"
#include "PinNames.h"

class UARTStateSender : public AbstractCmdSender {
    mbed::BufferedSerial* uart;

    public:
        UARTStateSender(PinName tx, PinName rx);
        ~UARTStateSender();

        virtual void sendCmd(Msg* msg) override;
};