#pragma once

#include "Task.h"

#include "StateTypes.h"
#include "AbstractFlapPosReader.h"
#include "AbstractFlapIndicator.h"
#include "AbstractStateExchange.h"


class BackSeat: public Task {
    
    flapState_t currentState{};
    
    AbstractFlapPosReader* reader;
    AbstractFlapIndicator* indicator;
    AbstractStateExchange* comm;

    public:
        BackSeat(AbstractFlapPosReader* reader, AbstractFlapIndicator* indicator, AbstractStateExchange* comm);

         void run() override;

};