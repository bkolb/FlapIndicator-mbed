#include "BackSeatVarioHandler.h"

#include "InterruptIn.h"
#include "Callback.h"

BackSeatVarioHandler::BackSeatVarioHandler(AbstractStateExchange* comm, PinName varioButtonPin): 
    AbstractVarioHandler(), 
    comm(comm)
    {
    varioBtn = new mbed::InterruptIn(varioButtonPin);
    varioBtn->rise(mbed::callback(this, &BackSeatVarioHandler::handleVarioButtonPressed));
}

BackSeatVarioHandler::~BackSeatVarioHandler(){
    delete varioBtn;
}

void BackSeatVarioHandler::handleVarioButtonPressed() {
    comm->sendVarioBtnPressed();
}