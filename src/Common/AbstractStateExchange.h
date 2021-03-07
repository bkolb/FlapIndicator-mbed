#pragma once

#include <cstddef>
#include <cstdint>

#include "Msg.h"
#include "Runnable.h"
#include "StateTypes.h"
#include "cmd/AbstractCmd.h"

#define CMDPARSER_SIZE 8

class AbstractCmdSender
{
  protected:
	virtual void sendCmd(Msg *msg) = 0;

  public:
	void sendCmd(AbstractCmd &cmd);
};

class AbstractCmdReceiver
{
  protected:
	AbstractCmdParser *cmdsParsers[CMDPARSER_SIZE];
	uint8_t cmdParserSize = 0;

	virtual void doReceive() = 0;

  public:
	void registerCmd(AbstractCmdParser *cmd);

	virtual void enqueueCmd(AbstractCmd &cmd) =0;
};