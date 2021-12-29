#pragma once

#include "PinNames.h"
#include "mbed.h"

#include "AbstractStateExchange.h"
#include "AbstractVarioHandler.h"
#include "InterruptIn.h"

class BackSeatVarioHandler : public AbstractVarioHandler
{
	AbstractCmdSender &comm;
	mbed::DigitalOut &varioLedPin;
	mbed::InterruptIn *varioBtn;

	bool btnPressedAndNotTransmitted;
	uint8_t counter;

  public:
	BackSeatVarioHandler(AbstractCmdSender &comm, PinName varioButtonPin, mbed::DigitalOut &varioLedPin);
	~BackSeatVarioHandler();

	void handleVarioButtonPressed() override;
	void run() override;
};