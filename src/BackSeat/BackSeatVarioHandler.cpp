#include "BackSeatVarioHandler.h"

#include "InterruptIn.h"
#include "Callback.h"

BackSeatVarioHandler::BackSeatVarioHandler(AbstractStateExchange* comm, PinName varioButtonPin): 
    AbstractVarioHandler(), 
    comm(comm)
    {
    varioBtn = new mbed::InterruptIn(varioButtonPin);
    varioBtn->mode(PullUp);
    varioBtn->fall(mbed::callback(this, &BackSeatVarioHandler::handleVarioButtonPressed));
}

BackSeatVarioHandler::~BackSeatVarioHandler(){
    delete varioBtn;
}

void BackSeatVarioHandler::run() {
    if(this->btnPressedAndNotTransmitted) {
        comm->sendVarioBtnPressed();
        this->btnPressedAndNotTransmitted=false;
    }
}

void BackSeatVarioHandler::handleVarioButtonPressed() {
    this->btnPressedAndNotTransmitted=true;
}