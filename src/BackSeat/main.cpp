#include "DigitalOut.h"
#include "PinNames.h"
#include "mbed.h"

#include "ADCFlapPosReader.h"
#include "DIOFlapIndicator.h"
#include "UARTStateExchange.h"

#include "BackSeat.h"


// main() runs in its own thread in the OS
int main()
{

    LedMapping leds {
        .led1 = DigitalOut(D0),
        .led2 = DigitalOut(D1),
        .led3 = DigitalOut(D2),
        .led4 = DigitalOut(D3),
        .led5 = DigitalOut(D4),
        .ledL = DigitalOut(D5)
    };


    ADCFlapPosReader reader(A0);
    DIOFlapIndicator indicator(&leds);
    UARTStateExchange comm(SERIAL_TX,SERIAL_RX);

    BackSeat bs(&reader, &indicator, &comm);
    while (true) {
        bs.run();    
        ThisThread::sleep_for(1s);
    }
}

