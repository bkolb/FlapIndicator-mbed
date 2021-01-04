#pragma once

struct flapState_t {
    bool led1;
    bool led2;
    bool led3;
    bool led4;
    bool led5;
    bool ledL;
};

struct systemState_t {
    flapState_t flapState;
    bool forceVario;
};