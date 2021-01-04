#pragma once

#include "StateTypes.h"
#include <cstddef>


#define BUFFER_SIZE 16

struct Msg {
    char* msgBuffer;
    std::size_t size;
};

class AbstractStateExchange {

    char msgBuffer[BUFFER_SIZE];

    protected:
        virtual auto sendString(Msg msg) -> void = 0;
        Msg convertToString(flapState_t state);

    public:
        void sendState(flapState_t state);
        void sendVarioBtnPressed();
};