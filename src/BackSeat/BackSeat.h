#pragma once

#include "Runnable.h"

#include "StateTypes.h"
#include "AbstractFlapPosReader.h"
#include "AbstractFlapIndicator.h"
#include "AbstractStateExchange.h"
#include "AbstractVarioHandler.h"


class BackSeat: public Runnable {
    
    flapState_t currentState{};
    
    AbstractFlapPosReader* reader;
    AbstractFlapIndicator* indicator;
    AbstractCmdSender* comm;
    AbstractVarioHandler* vario;

    public:
        BackSeat(AbstractFlapPosReader* reader, AbstractFlapIndicator* indicator, AbstractCmdSender* comm, AbstractVarioHandler* vario);

         void run() override;

};