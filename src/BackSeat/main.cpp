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
								.LL_MAX         = 18000,

                                .L5_MIN         = 18330,
								.L5_MAX         = 18380,

                                .L4_MIN         = 24580,
								.L4_MAX         = 31457,

                                .L3_MIN         = 31459,
								.L3_MAX         = 45148,

                                .L2_MIN         = 45150,
								.L2_MAX         = 58404,

                                .L1_MIN         = 58406,
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
