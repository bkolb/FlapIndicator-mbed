#include "mbed.h"

#include "PinNames.h"

#include "ADCFlapPosReader.h"
#include "DIOFlapIndicator.h"
#include "DigitalOut.h"
#include "UARTStateExchange.h"

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


// main() runs in its own thread in the OS
int main()
{
	while (true) {
		uint16_t raw = reader.readRawVal();
		printf("%u\n", raw);

		ThisThread::sleep_for(250ms);
	}
	return 0;
}
