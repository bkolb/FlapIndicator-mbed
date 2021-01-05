#pragma once

#include "StateTypes.h"
#include <cstddef>


#define BUFFER_SIZE 32

struct Msg {
    char* msgBuffer;
    std::size_t size;
};

class AbstractStateExchange {

    char msgBuffer[BUFFER_SIZE];

    protected:
        Msg convertToString(flapState_t state);

    public:
        virtual auto sendString(Msg msg) -> void = 0;

        void sendState(flapState_t state);
        void sendVarioBtnPressed();
};