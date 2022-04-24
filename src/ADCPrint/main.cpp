#include "mbed.h"

#include "PinNames.h"

#include "ADCFlapPosReader.h"
#include "DIOFlapIndicator.h"
#include "DigitalOut.h"
#include "UARTStateExchange.h"

RavVal2LedThreshold raw2led {
                                .LL_VAL         = 10900,
                                .L5_VAL         = 21300,
                                .L4_VAL         = 22800,
                                .L3_VAL         = 28300,
                                .L2_VAL         = 32400,
                                .L1_VAL         = 37800,
                                .OFFSET         = 700,
								.OFFSET_L         = 1000,
                        };

ADCFlapPosReader reader(A0, raw2led);

PinName varioButtonPin = A3;
mbed::InterruptIn *varioBtn;

//FlashIAP flash;

#define COUNT 100
#define CYCLES 3

#define cursup    "\033[A"

bool buttonPressed;

void handleVarioButtonPressed()
{
	buttonPressed = true;
}


void calcAvgValue(char flap, uint16_t *min, uint16_t *max) {
	buttonPressed = false;
	printf("  * Set flap to %c and press vario button to continue\n", flap);
	//pc._getc();
	while(!buttonPressed){
		ThisThread::sleep_for(50ms);
	}

	uint8_t ctr = 0;

	while(ctr < COUNT){
		uint16_t rawValue = reader.readRawVal();
		if(*min > rawValue) {
			*min = rawValue;
		}
		if(*max < rawValue) {
			*max = rawValue;
		}

		printf("\r    ==> %u (%u)", ctr, rawValue);
		fflush(stdout);
		ctr++;
		ThisThread::sleep_for(50ms);
	}
	//printf(cursup);
	printf(cursup);
	fflush(stdout);
}

uint16_t avgValue(uint16_t min, uint16_t max) {
	uint16_t halfDiff = (max-min)/2;
	uint16_t res = max - halfDiff;

	return res;
}


// main() runs in its own thread in the OS
int main()
{

	varioBtn = new mbed::InterruptIn(varioButtonPin);
	varioBtn->mode(PullUp);
	varioBtn->fall(mbed::callback(&handleVarioButtonPressed));
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

	printf("=== Starting Calibration ===\n");

	uint8_t cycle = 0;

	while(cycle<CYCLES) {
		cycle++;
		printf("= Cycle %c of %c =\n",cycle, CYCLES);
		calcAvgValue('L', &flap_Lmin, &flap_Lmax);
		calcAvgValue('5', &flap_5min, &flap_5max);
		calcAvgValue('4', &flap_4min, &flap_4max);
		calcAvgValue('3', &flap_3min, &flap_3max);
		calcAvgValue('2', &flap_2min, &flap_2max);
		calcAvgValue('1', &flap_1min, &flap_1max);
	}

	printf("\n");
	printf("\n");
	printf("\n");
	printf("=== Calibration Finished ===\n");
	printf("\n");

	printf("RavVal2LedThreshold raw2led {\n");
	printf("				.LL_VAL		= %u,\n", avgValue(flap_Lmin, flap_Lmax));
	printf("				.L5_VAL		= %u,\n", avgValue(flap_5min, flap_5max));
	printf("				.L4_VAL		= %u,\n", avgValue(flap_4min, flap_4max));
	printf("				.L3_VAL		= %u,\n", avgValue(flap_3min, flap_3max));
	printf("				.L2_VAL		= %u,\n", avgValue(flap_2min, flap_2max));
	printf("				.L1_VAL		= %u,\n", avgValue(flap_1min, flap_1max));
	printf("				.OFFSET		= 700,\n");
	printf("				.OFFSET_L		= 1000;\n");
	printf("			};\n"									);


	return 0;
}
