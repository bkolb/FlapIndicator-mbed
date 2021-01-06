#pragma once

#include "AbstractFlapIndicator.h"
#include "AbstractFlapPosReader.h"
#include "AbstractStateExchange.h"
#include "AbstractVarioHandler.h"
#include "Runnable.h"
#include "StateTypes.h"

class BackSeat : public Runnable
{
	flapState_t currentState {};

	AbstractFlapPosReader &reader;
	AbstractFlapIndicator &indicator;
	AbstractCmdSender &comm;
	AbstractVarioHandler &vario;

  public:
	BackSeat(AbstractFlapPosReader &reader, AbstractFlapIndicator &indicator, AbstractCmdSender &comm,
			 AbstractVarioHandler &vario);

	void run() override;
};