#pragma once

#include "PinNames.h"

#include "AbstractStateExchange.h"
#include "AbstractVarioHandler.h"
#include "InterruptIn.h"

class FrontSeatVarioHandler : public AbstractVarioHandler
{
	AbstractCmdReceiver &comm;
	mbed::InterruptIn *varioBtn;

	bool btnPressedAndNotHandled;
	uint8_t counter;

  public:
	FrontSeatVarioHandler(AbstractCmdReceiver &comm, PinName varioButtonPin);
	~FrontSeatVarioHandler();

	void handleVarioButtonPressed() override;
	void run() override;
};