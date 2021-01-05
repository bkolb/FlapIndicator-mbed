#pragma once

#include "StateTypes.h"

#include "Msg.h"

#include "cmd/AbstractCmd.h"
#include <cstddef>
#include <cstdint>



#define CMD_SIZE 8

#define BUFFER_SIZE 32

class AbstractCmdSender {

    protected:
        Msg msg;
        virtual void sendCmd(Msg* msg) = 0;

    public:
        AbstractCmdSender() {
            char* msgBuffer = new char[BUFFER_SIZE];
            msg.msgBuffer = msgBuffer;
        }

        ~AbstractCmdSender(){
            delete msg.msgBuffer;
        }

        void registerCmd(AbstractCmd* cmd);
        
        void sendCmd(AbstractCmd* cmd);
};

class AbstractCmdReceiver {
    
    AbstractCmd* cmds[CMD_SIZE];
    uint8_t cmdSize = 0;

    protected:
        Msg msg;

    public:
        AbstractCmdReceiver() {
            char* msgBuffer = new char[BUFFER_SIZE];
            msg.msgBuffer = msgBuffer;
        }

        ~AbstractCmdReceiver(){
            delete msg.msgBuffer;
        }

        void registerCmd(AbstractCmd* cmd);
};