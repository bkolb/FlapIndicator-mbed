#include "mbed.h"

#include "PinNames.h"

#include "ADCFlapPosReader.h"
#include "BackSeat.h"
#include "BackSeatVarioHandler.h"
#include "DIOFlapIndicator.h"
#include "DigitalOut.h"
#include "UARTStateExchange.h"

LedMapping leds {.led1 = DigitalOut(D10),
				 .led2 = DigitalOut(D9),
				 .led3 = DigitalOut(D6),
				 .led4 = DigitalOut(D5),
				 .led5 = DigitalOut(D4),
				 .ledL = DigitalOut(D3)};

RavVal2LedThreshold raw2led {
                                .LL_VAL         = 11048,
                                .L5_VAL         = 21594,
                                .L4_VAL         = 22895,
                                .L3_VAL         = 28373,
                                .L2_VAL         = 32602,
                                .L1_VAL         = 37664,
                                .OFFSET         = 700,
                                .OFFSET_L               = 1000
                        };
			

ADCFlapPosReader reader(A0, raw2led);
DIOFlapIndicator indicator(leds);
UARTStateSender comm(PA_2);

mbed::DigitalOut varioLedPin(D13);

BackSeatVarioHandler vario(comm, A3, varioLedPin);

BackSeat bs(reader, indicator, comm, vario);

// main() runs in its own thread in the OS
int main()
{
	while (true) {
		bs.run();
		ThisThread::sleep_for(50ms);
	}

	return 0;
}
