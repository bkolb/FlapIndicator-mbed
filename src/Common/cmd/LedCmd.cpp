

#include "LedCmd.h"

#include "../StateTypes.h"


#define ASSIGN(CHAR) \
    state.led##CHAR = c2b(msg->msgBuffer[msg->pos++]); \

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
    msg->msgBuffer[msg->pos++] = '1';
    msg->msgBuffer[msg->pos++] = b2c(state.led1);

    msg->msgBuffer[msg->pos++] = '2';
    msg->msgBuffer[msg->pos++] = b2c(state.led2);

    msg->msgBuffer[msg->pos++] = '3';
    msg->msgBuffer[msg->pos++] = b2c(state.led3);

    msg->msgBuffer[msg->pos++] = '4';
    msg->msgBuffer[msg->pos++] = b2c(state.led4);

    msg->msgBuffer[msg->pos++] = '5';
    msg->msgBuffer[msg->pos++] = b2c(state.led5);

    msg->msgBuffer[msg->pos++] = 'L';
    msg->msgBuffer[msg->pos++] = b2c(state.ledL);   
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
    vario->updateVario(state);
    flapIndicator->updateState(state);
}

char LedCmdParser::cmdID(){
    return LED_CMD_ID;
}