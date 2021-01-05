#include "AbstractCmd.h"

void AbstractCmd::toMsg(Msg* msg) {
    msg->size=0;
    msg->msgBuffer[msg->size++] = cmdID();

    this->toMsgInternal(msg);

    msg->msgBuffer[msg->size++] = EndOfCommand;
    msg->msgBuffer[msg->size++] = 0;
}

bool AbstractCmdParser::parseAndHandleMsg(Msg* msg) {
    CHECK(cmdID())

    parseMsgInternal(msg);

    CHECK(EndOfCommand)

    handleMsgInternal();
    msg->msgBuffer[0]=0;
    return true;
}