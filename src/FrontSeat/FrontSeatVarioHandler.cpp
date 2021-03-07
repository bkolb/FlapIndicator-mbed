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
}

FrontSeatVarioHandler::~FrontSeatVarioHandler()
{
	delete varioBtn;
}

void FrontSeatVarioHandler::run()
{
	if (this->btnPressedAndNotHandled) {
		VarioCmd vario;
		comm.enqueueCmd(vario);

		this->btnPressedAndNotHandled = false;
	}
}

void FrontSeatVarioHandler::handleVarioButtonPressed()
{
	this->btnPressedAndNotHandled = true;
}