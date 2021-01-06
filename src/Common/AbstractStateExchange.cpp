#include "AbstractStateExchange.h"

#include <cstdint>


void AbstractCmdReceiver::registerCmd(AbstractCmdParser* cmd) {
    if(cmdParserSize<CMDPARSER_SIZE){
        this->cmdsParsers[cmdParserSize++] = cmd;
    }
}
        
void AbstractCmdSender::sendCmd(AbstractCmd* cmd) {
    Msg msg;
    cmd->toMsg(&msg);
    sendCmd(&msg);
}