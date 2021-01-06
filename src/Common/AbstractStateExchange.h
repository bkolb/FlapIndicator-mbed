#pragma once

#include "StateTypes.h"

#include "Msg.h"
#include "Runnable.h"

#include "cmd/AbstractCmd.h"

#include <cstddef>
#include <cstdint>



#define CMDPARSER_SIZE 8



class AbstractCmdSender {

    protected:
        virtual void sendCmd(Msg* msg) = 0;

    public:
        void sendCmd(AbstractCmd& cmd);
};

class AbstractCmdReceiver {
    
    protected:
        AbstractCmdParser* cmdsParsers[CMDPARSER_SIZE];
        uint8_t cmdParserSize = 0;

        virtual void doReceive() = 0;

    public:
        void registerCmd(AbstractCmdParser* cmd);
};