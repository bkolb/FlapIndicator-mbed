#pragma once

#include "StateTypes.h"

class AbstractVarioOut {

    flapState_t currentState;

    public:
        virtual bool isVario() =0;
        virtual void setVario(bool v) =0;

        void updateVario(flapState_t newState);

        void toggleVario();

    private:
        bool requireVario(flapState_t state);
};