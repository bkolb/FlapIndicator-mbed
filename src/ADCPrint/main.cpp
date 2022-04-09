#include "mbed.h"
#include "USBSerial.h"

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

USBSerial pc;
//FlashIAP flash;

#define COUNT 100
#define CYCLES 4

#define cursup    "\033[A"

void calcAvgValue(char flap, uint16_t *min, uint16_t *max) {
	pc.printf("  * Set flap to %c and press key to continue\n", flap);
	pc._getc();

	uint8_t ctr = 0;

	while(ctr < COUNT){
		uint16_t rawValue = reader.readRawVal();
		if(*min > rawValue) {
			*min = rawValue;
		}
		if(*max < rawValue) {
			*max = rawValue;
		}

		pc.printf("\r    ==> %u", ctr);
		pc.sync();
		ctr++;
		ThisThread::sleep_for(50ms);
	}
	pc.printf(cursup);
	pc.printf(cursup);
	pc.sync();
}


// main() runs in its own thread in the OS
int main()
{
	/*
	while (true) {
		uint16_t raw = reader.readRawVal();
		printf("%u\n", raw);

		ThisThread::sleep_for(250ms);
	}
	*/
	uint16_t flap_Lmin = 65000;
	uint16_t flap_Lmax = 0;
	
	uint16_t flap_5min = 65000;
	uint16_t flap_5max = 0;
	
	uint16_t flap_4min = 65000;
	uint16_t flap_4max = 0;
	
	uint16_t flap_3min = 65000;
	uint16_t flap_3max = 0;
	
	uint16_t flap_2min = 65000;
	uint16_t flap_2max = 0;
	
	uint16_t flap_1min = 65000;
	uint16_t flap_1max = 0;

	pc.printf("=== Starting Calibration ===\n");

	uint8_t cycle = 0;

	while(cycle<CYCLES) {
		cycle++;
		pc.printf("= Cycle %c of %c =\n",cycle, CYCLES);
		calcAvgValue('L', &flap_Lmin, &flap_Lmax);
		calcAvgValue('5', &flap_5min, &flap_5max);
		calcAvgValue('4', &flap_4min, &flap_4max);
		calcAvgValue('3', &flap_3min, &flap_3max);
		calcAvgValue('2', &flap_2min, &flap_2max);
		calcAvgValue('1', &flap_1min, &flap_1max);
	}

	pc.printf("\n");
	pc.printf("=== Calibration Finished ===\n");
	pc.printf("\n");

	pc.printf("RavVal2LedThreshold raw2led {\n");
	pc.printf("				.LL_VAL		= %u,\n", flap_5min-50);
	pc.printf("				.LL_L5_VAL 	= %u,\n", flap_5min-10);
	pc.printf("				.L5_VAL		= %u,\n", flap_5max+50);
	pc.printf("				.L5_L4_VAL 	= %u,\n", flap_4min-50);
	pc.printf("				.L4_VAL		= %u,\n", flap_4max+50);
	pc.printf("				.L4_L3_VAL 	= %u,\n", flap_3min-50);
	pc.printf("				.L3_VAL		= %u,\n", flap_3max+50);
	pc.printf("				.L3_L2_VAL 	= %u,\n", flap_2min-50);
	pc.printf("				.L2_VAL		= %u,\n", flap_2max+50);
	pc.printf("				.L2_L1_VAL 	= %u,\n", flap_1min-50);
	pc.printf("				.L1_VAL		= %u\n" , flap_1max+50);
	pc.printf("			};\n"									);


	return 0;
}
