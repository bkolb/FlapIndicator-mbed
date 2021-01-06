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

ADCFlapPosReader reader(A0);
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
