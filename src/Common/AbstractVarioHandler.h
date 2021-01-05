#pragma once

#include "StateTypes.h"

#include "Runnable.h"

class AbstractVarioHandler: public Runnable {

    public:
        virtual void handleVarioButtonPressed() = 0;

        void run() override;

};