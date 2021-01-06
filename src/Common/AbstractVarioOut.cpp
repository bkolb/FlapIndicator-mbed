#include "AbstractVarioOut.h"

void AbstractVarioOut::updateVario(flapState_t state){
    bool prevVario = requireVario(currentState);
    bool thisVario = requireVario(state);

    // we only switch if we have a state change. Otherwise we want 
    // to preserve the current state
    if(prevVario && !thisVario){
        setVario(false);
    } else if(!prevVario && thisVario) {
        setVario(true);
    }

    currentState = state;
}

bool AbstractVarioOut::requireVario(flapState_t state){
    return !state.led1 && !state.led2 && !state.led3;
}

void AbstractVarioOut::toggleVario() {
    setVario(!isVario());
}