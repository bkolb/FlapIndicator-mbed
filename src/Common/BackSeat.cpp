#include "BackSeat.h"

BackSeat::BackSeat(AbstractFlapPosReader* reader, AbstractFlapIndicator* indicator, AbstractStateExchange* comm): 
    Task(), 
    reader(reader),
    indicator(indicator),
    comm(comm) 
{}

void BackSeat::run() {
    flapState_t newState = reader->currentState();
    
    currentState = newState;
    comm->sendState(currentState);
    indicator->updateState(currentState);
}