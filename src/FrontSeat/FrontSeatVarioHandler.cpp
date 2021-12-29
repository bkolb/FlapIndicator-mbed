#include "FrontSeatVarioHandler.h"

#include "Callback.h"
#include "InterruptIn.h"
#include "cmd/VarioCmd.h"

FrontSeatVarioHandler::FrontSeatVarioHandler(AbstractCmdReceiver &comm, PinName varioButtonPin)
	: AbstractVarioHandler(), comm(comm)
{
	varioBtn = new mbed::InterruptIn(varioButtonPin);
	varioBtn->mode(PullUp);
	varioBtn->fall(mbed::callback(this, &FrontSeatVarioHandler::handleVarioButtonPressed));
	btnPressedAndNotHandled = false;
	counter = 0;
}

FrontSeatVarioHandler::~FrontSeatVarioHandler()
{
	delete varioBtn;
}

void FrontSeatVarioHandler::run()
{
	if (this->btnPressedAndNotHandled && this->counter == 0) {
		VarioCmd vario;
		comm.enqueueCmd(vario);
		this->counter = 1;
	}
	else if(counter>0) {
		this->counter -= 1;
	}
	this->btnPressedAndNotHandled = false;
}

void FrontSeatVarioHandler::handleVarioButtonPressed()
{
	this->btnPressedAndNotHandled = true;
}