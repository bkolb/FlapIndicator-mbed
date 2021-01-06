#include "BackSeatVarioHandler.h"

#include "InterruptIn.h"
#include "Callback.h"

#include "cmd/VarioCmd.h"

BackSeatVarioHandler::BackSeatVarioHandler(AbstractCmdSender& comm, PinName varioButtonPin): 
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

        VarioCmd vario;
        comm.sendCmd(vario);
        
        this->btnPressedAndNotTransmitted=false;
    }
}

void BackSeatVarioHandler::handleVarioButtonPressed() {
    this->btnPressedAndNotTransmitted=true;
}