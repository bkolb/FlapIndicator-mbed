#pragma once

#include "AbstractStateExchange.h"

#include "BufferedSerial.h"
#include "UnbufferedSerial.h"
#include "PinNames.h"

#include "Runnable.h"

#include "Mail.h"

class UARTStateSender : public AbstractCmdSender {
    mbed::BufferedSerial* uart;

    public:
        UARTStateSender(PinName tx);
        ~UARTStateSender();

        virtual void sendCmd(Msg* msg) override;
};

class UARTStateReceiver : public AbstractCmdReceiver, public Runnable {
    mbed::UnbufferedSerial* uart;

    rtos::Mail<Msg, 16> mail_box;
    Msg* currentMsg;

    protected:
        virtual void doReceive() override;

    public:
        UARTStateReceiver(PinName rx);
        ~UARTStateReceiver();

        void run() override;
};