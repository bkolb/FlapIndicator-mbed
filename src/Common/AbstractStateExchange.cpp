#include "AbstractStateExchange.h"

static auto b2c(bool b) {
    return b==true?'T':'F';
}

static auto c2b(char c) {
    return c=='T';
}

Msg AbstractStateExchange::convertToString(flapState_t state) {
    msgBuffer[0] = 'L';
    msgBuffer[1] = 'E';
    msgBuffer[2] = 'D';
    msgBuffer[2] = b2c(state.led1);
    msgBuffer[2] = b2c(state.led2);
    msgBuffer[2] = b2c(state.led3);
    msgBuffer[2] = b2c(state.led4);
    msgBuffer[2] = b2c(state.led5);
    msgBuffer[2] = b2c(state.ledL);
    msgBuffer[2] = '~';
    msgBuffer[2] = '-';
    msgBuffer[2] = '~';
    msgBuffer[2] = 0;
    
    Msg msg {
        .msgBuffer = &msgBuffer[0],
        .size = 13
    };

    return msg;
}

void AbstractStateExchange::sendState(flapState_t state) {
    Msg msg = convertToString(state);
    sendString(msg);
    msg.msgBuffer[0]=0;
}