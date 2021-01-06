#pragma once

#include "../Msg.h"

#define BeginOfCommand '\n'
#define EndOfCommand 0

#define LED_CMD_ID 'L'
#define VARIO_CMD_ID 'V'

#define CHECK(CHAR) \
    { \
        char c = msg->msgBuffer[msg->pos++];\
        if(c != (CHAR)) {\
            return false; \
        } \
    } \


class AbstractCmd {

    public:
        virtual char cmdID() = 0;

        void toMsg(Msg* msg);

    protected:
        virtual void toMsgInternal(Msg* msg) = 0;
    
};

class AbstractCmdParser {

    public:
        virtual char cmdID() = 0;

        bool parseAndHandleMsg(Msg* msg);

    protected: 
        virtual bool parseMsgInternal(Msg* msg) = 0;

        virtual void handleMsgInternal() = 0;
};