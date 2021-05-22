

#include "VarioCmd.h"
#include <cstdio>

#include "../StateTypes.h"

void VarioCmd::toMsgInternal(Msg *msg) {
	msg->msgBuffer[msg->pos++] = 'V';
	msg->msgBuffer[msg->pos++] = 'A';
	msg->msgBuffer[msg->pos++] = 'R';
	msg->msgBuffer[msg->pos++] = 'I';
	msg->msgBuffer[msg->pos++] = 'O';
}

char VarioCmd::cmdID()
{
	return VARIO_CMD_ID;
}

bool VarioCmdParser::parseMsgInternal(Msg *msg)
{
	CHECK('V')
	CHECK('A')
	CHECK('R')
	CHECK('I')
	CHECK('O')
	return true;
};

void VarioCmdParser::handleMsgInternal()
{
	vario.toggleVario();
}

char VarioCmdParser::cmdID()
{
	return VARIO_CMD_ID;
}