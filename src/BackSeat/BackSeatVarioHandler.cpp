#include "BackSeatVarioHandler.h"

#include "Callback.h"
#include "InterruptIn.h"
#include "cmd/VarioCmd.h"

BackSeatVarioHandler::BackSeatVarioHandler(AbstractCmdSender &comm, PinName varioButtonPin, mbed::DigitalOut &varioLedPin)
	: AbstractVarioHandler(), comm(comm), varioLedPin(varioLedPin)
{
	varioBtn = new mbed::InterruptIn(varioButtonPin);
	varioBtn->mode(PullUp);
	varioBtn->fall(mbed::callback(this, &BackSeatVarioHandler::handleVarioButtonPressed));
	btnPressedAndNotTransmitted = false;
	counter = 0;
	}

BackSeatVarioHandler::~BackSeatVarioHandler()
{
	delete varioBtn;
}

void BackSeatVarioHandler::run()
{
	if (this->btnPressedAndNotTransmitted && this->counter == 0) {
		VarioCmd vario;
		comm.sendCmd(vario);
		this->counter = 1;
	}
	else if(counter>0) {
		this->counter -= 1;
	}
	this->btnPressedAndNotTransmitted = false;
}

void BackSeatVarioHandler::handleVarioButtonPressed()
{
	this->btnPressedAndNotTransmitted = true;
}