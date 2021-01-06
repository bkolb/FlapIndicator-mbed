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

RavVal2LedThreshold raw2led {.LL_VAL	= 10000,
					.LL_L5_VAL = 15000,
					.L5_VAL	= 20000,
					.L5_L4_VAL = 25000,
					.L4_VAL	= 30000,
					.L4_L3_VAL = 35000,
					.L3_VAL	= 40000,
					.L3_L2_VAL = 45000,
					.L2_VAL	= 50000,
					.L2_L1_VAL = 55000,
					.L1_VAL	= 60000};				

ADCFlapPosReader reader(A0, raw2led);
DIOFlapIndicator indicator(leds);
UARTStateSender comm(PA_2);

BackSeatVarioHandler vario(comm, A3);

BackSeat bs(reader, indicator, comm, vario);

// main() runs in its own thread in the OS
int main()
{
	while (true) {
		bs.run();
		ThisThread::sleep_for(500ms);
	}

	return 0;
}
