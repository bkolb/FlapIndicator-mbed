#pragma once

#include "AbstractCmd.h"
#include "../AbstractFlapIndicator.h"

#include "../Msg.h"

#include <cstdint>

class LedCmd : public AbstractCmd {

    flapState_t state;

    public:
        LedCmd(flapState_t state): AbstractCmd(), state(state){};
        
        char cmdID() override;
        
        void toMsgInternal(Msg* msg) override;

};

class LedCmdParser : public AbstractCmdParser {

    flapState_t state;
    AbstractFlapIndicator* flapIndicator;

    public:
        LedCmdParser(AbstractFlapIndicator* flapIndicator): flapIndicator(flapIndicator){};
        char cmdID() override;
        
        virtual bool parseMsgInternal(Msg* msg) override;

        virtual void handleMsgInternal() override;

};