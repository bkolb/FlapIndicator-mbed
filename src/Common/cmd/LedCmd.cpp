

#include "LedCmd.h"

#include "../StateTypes.h"


#define ASSIGN(CHAR) \
    state.led##CHAR = c2b(msg->msgBuffer[msg->size++]); \

static auto b2c(bool b) {
    return b==true?'T':'F';
}

static auto c2b(char c) {
    return c=='T';
}

char LedCmd::cmdID(){
    return LED_CMD_ID;
}
        
void LedCmd::toMsgInternal(Msg* msg) {
    msg->msgBuffer[msg->size++] = '1';
    msg->msgBuffer[msg->size++] = b2c(state.led1);

    msg->msgBuffer[msg->size++] = '2';
    msg->msgBuffer[msg->size++] = b2c(state.led2);

    msg->msgBuffer[msg->size++] = '3';
    msg->msgBuffer[msg->size++] = b2c(state.led3);

    msg->msgBuffer[msg->size++] = '4';
    msg->msgBuffer[msg->size++] = b2c(state.led4);

    msg->msgBuffer[msg->size++] = '5';
    msg->msgBuffer[msg->size++] = b2c(state.led5);

    msg->msgBuffer[msg->size++] = 'L';
    msg->msgBuffer[msg->size++] = b2c(state.ledL);   
}

bool LedCmdParser::parseMsgInternal(Msg* msg) { 
    CHECK('1')
    ASSIGN(1)
    
    CHECK('2')
    ASSIGN(2)
    
    CHECK('3')
    ASSIGN(3)
    
    CHECK('4')
    ASSIGN(4)
    
    CHECK('5')
    ASSIGN(5)
    
    CHECK('L')
    ASSIGN(L)

    

    return true;
};

void LedCmdParser::handleMsgInternal() {
    flapIndicator->updateState(state);
}

char LedCmdParser::cmdID(){
    return LED_CMD_ID;
}