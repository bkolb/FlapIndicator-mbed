#include "BackSeat.h"

BackSeat::BackSeat(AbstractFlapPosReader* reader, AbstractFlapIndicator* indicator, AbstractStateExchange* comm): 
    Task(), 
    reader(reader),
    indicator(indicator),
    comm(comm) 
{}

void BackSeat::run() {
    flapState_t newState = reader->currentState();
    if(currentState!=newState) {
        currentState = newState;
        comm->sendState(currentState);
        indicator->updateState(currentState);
    }
}