#include "AbstractCmd.h"

#include <cstdio>

void AbstractCmd::toMsg(Msg* msg) {
    msg->pos=0;
    msg->msgBuffer[msg->pos++] = BeginOfCommand;
    msg->msgBuffer[msg->pos++] = cmdID();

    this->toMsgInternal(msg);

    msg->msgBuffer[msg->pos++] = EndOfCommand;
    msg->msgBuffer[msg->pos++] = 0;
}

bool AbstractCmdParser::parseAndHandleMsg(Msg* msg) {
    // in case the message was processed before, we reset the position to the beginning
    msg->pos=0;

    CHECK(BeginOfCommand)
    CHECK(cmdID());

    parseMsgInternal(msg);

    CHECK(EndOfCommand)

    handleMsgInternal();

    return true;
}