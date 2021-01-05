#pragma once

#include "AbstractCmd.h"
#include "../AbstractFlapIndicator.h"

#include "../Msg.h"

#include <cstdint>

class VarioCmd : public AbstractCmd {

    public:
        char cmdID() override;
        
        void toMsgInternal(Msg* msg) override;

};

class VarioCmdParser : public AbstractCmdParser {

    public:
        char cmdID() override;
        
        virtual bool parseMsgInternal(Msg* msg) override;

        virtual void handleMsgInternal() override;

};