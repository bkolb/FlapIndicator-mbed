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
					.LL_VAL		=		20693	,
					.LL_L5_VAL 	=		20733	,	
					.L5_VAL		=		21260	,
					.L5_L4_VAL 	=		22102	,	
					.L4_VAL		=		22683	,
					.L4_L3_VAL 	=		27016	,	
					.L3_VAL		=		27605	,
					.L3_L2_VAL 	=		31629	,	
					.L2_VAL		=		32183	,
					.L2_L1_VAL 	=		36938	,	
					.L1_VAL		=		37381	
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
