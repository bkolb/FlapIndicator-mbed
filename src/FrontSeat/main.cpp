// Mbed CMake Template
// Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
// SPDX-License-Identifier: Apache-2.0

#include "mbed.h"

#include "DIOFlapIndicator.h"
#include "UARTStateExchange.h"

LedMapping leds {
    .led1 = DigitalOut(D10),
    .led2 = DigitalOut(D9),
    .led3 = DigitalOut(D6),
    .led4 = DigitalOut(D5),
    .led5 = DigitalOut(D4),
    .ledL = DigitalOut(D3)
};

DIOFlapIndicator indicator = DIOFlapIndicator(&leds);
//UARTStateExchange comm = UARTStateExchange(SERIAL_TX,SERIAL_RX);

static BufferedSerial serial_port(USBTX, USBRX);

#define MAXIMUM_BUFFER_SIZE                                                  32

int main(void)
{
	// Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(
        /* bits */ 8,
        /* parity */ BufferedSerial::None,
        /* stop bit */ 1
    );

	// Application buffer to receive the data
    char buf[MAXIMUM_BUFFER_SIZE] = {0};

//	hello.start();

	while (true) {
		if (uint32_t num = serial_port.read(buf, sizeof(buf))) {
            // Toggle the LED.
            //led = !led;
        }
	}

	return 0;
}
