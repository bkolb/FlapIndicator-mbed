#include "AbstractStateExchange.h"

#include <cstdint>

static auto b2c(bool b) {
    return b==true?'T':'F';
}

static auto c2b(char c) {
    return c=='T';
}

Msg AbstractStateExchange::convertToString(flapState_t state) {
    uint8_t ctr = 0;

    msgBuffer[ctr++] = '1';
    msgBuffer[ctr++] = b2c(state.led1);

    msgBuffer[ctr++] = '2';
    msgBuffer[ctr++] = b2c(state.led2);

    msgBuffer[ctr++] = '3';
    msgBuffer[ctr++] = b2c(state.led3);

    msgBuffer[ctr++] = '4';
    msgBuffer[ctr++] = b2c(state.led4);

    msgBuffer[ctr++] = '5';
    msgBuffer[ctr++] = b2c(state.led5);

    msgBuffer[ctr++] = 'L';
    msgBuffer[ctr++] = b2c(state.ledL);
    
    msgBuffer[ctr++] = '\n';
    msgBuffer[ctr++] = 0;
    
    Msg msg {
        .msgBuffer = &msgBuffer[0],
        .size = ctr
    };

    return msg;
}

void AbstractStateExchange::sendState(flapState_t state) {
    Msg msg = convertToString(state);
    sendString(msg);
    msg.msgBuffer[0]=0;
}