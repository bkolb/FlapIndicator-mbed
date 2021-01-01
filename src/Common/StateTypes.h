#pragma once

struct flapState_t {
    bool led1;
    bool led2;
    bool led3;
    bool led4;
    bool led5;
    bool ledL;

    bool operator!=(const flapState_t& other) const 
    {
    return led1 != other.led1 && 
        led2 != other.led2 &&
        led3 != other.led3 &&
        led4 != other.led4 &&
        led5 != other.led5 &&
        ledL != other.ledL;
    }
};

struct systemState_t {
    flapState_t flapState;
    bool forceVario;
};