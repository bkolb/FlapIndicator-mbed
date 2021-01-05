

#include "VarioCmd.h"

#include "../StateTypes.h"
       
void VarioCmd::toMsgInternal(Msg* msg) {
}

char VarioCmd::cmdID(){
    return VARIO_CMD_ID;
}

bool VarioCmdParser::parseMsgInternal(Msg* msg) { 
    return true;
};

void VarioCmdParser::handleMsgInternal() {
    // TODO
}

char VarioCmdParser::cmdID(){
    return VARIO_CMD_ID;
}