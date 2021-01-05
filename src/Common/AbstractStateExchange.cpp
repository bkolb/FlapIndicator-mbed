#include "AbstractStateExchange.h"

#include <cstdint>


void AbstractCmdReceiver::registerCmd(AbstractCmd* cmd) {
    this->cmds[cmdSize] = cmd;
    cmdSize++;
}
        
void AbstractCmdSender::sendCmd(AbstractCmd* cmd) {
    cmd->toMsg(&msg);
    sendCmd(&msg);   
    msg.msgBuffer[0]=0;
}