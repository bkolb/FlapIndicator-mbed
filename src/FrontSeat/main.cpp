// Mbed CMake Template
// Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
// SPDX-License-Identifier: Apache-2.0

#include "mbed.h"

#include "DIOFlapIndicator.h"
#include "UARTStateExchange.h"
#include "VarioOut.h"
#include "cmd/LedCmd.h"
#include "cmd/VarioCmd.h"

LedMapping leds {.led1 = mbed::DigitalOut(D10),
				 .led2 = mbed::DigitalOut(D9),
				 .led3 = mbed::DigitalOut(D6),
				 .led4 = mbed::DigitalOut(D5),
				 .led5 = mbed::DigitalOut(D4),
				 .ledL = mbed::DigitalOut(D3)};

// TODO change
//mbed::DigitalOut varioPin(LED1);
mbed::DigitalOut varioPin(D11);

VarioOut vario(varioPin);

DIOFlapIndicator indicator(leds);
UARTStateReceiver comm(PA_10);

LedCmdParser ledParser(indicator, vario);
VarioCmdParser varioParser(vario);

rtos::Thread thread;

int main(void)
{
	comm.registerCmd(&ledParser);
	comm.registerCmd(&varioParser);

	thread.start(mbed::callback(&comm, &Runnable::run));

	while (true) {
		ThisThread::sleep_for(500ms);
	}

	return 0;
}
