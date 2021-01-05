#include "BackSeat.h"

BackSeat::BackSeat(AbstractFlapPosReader* reader, AbstractFlapIndicator* indicator, AbstractStateExchange* comm, AbstractVarioHandler* vario): 
    Runnable(), 
    reader(reader),
    indicator(indicator),
    comm(comm),
    vario(vario) {
}

void BackSeat::run() {
    flapState_t newState = reader->currentState();
    currentState = newState;
    comm->sendState(currentState);
    indicator->updateState(currentState);
    vario->run();
}