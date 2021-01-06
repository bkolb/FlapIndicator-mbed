#pragma once

#include "PinNames.h"

#include "AbstractStateExchange.h"
#include "AbstractVarioHandler.h"
#include "InterruptIn.h"

class BackSeatVarioHandler : public AbstractVarioHandler
{
	AbstractCmdSender &comm;
	mbed::InterruptIn *varioBtn;

	bool btnPressedAndNotTransmitted;

  public:
	BackSeatVarioHandler(AbstractCmdSender &comm, PinName varioButtonPin);
	~BackSeatVarioHandler();

	void handleVarioButtonPressed() override;
	void run() override;
};