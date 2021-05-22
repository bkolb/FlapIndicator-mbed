// Mbed CMake Template
// Copyright 2020 Ladislas de Toldi (ladislas [at] detoldi.me)
// SPDX-License-Identifier: Apache-2.0

#include "mbed.h"

#include "DIOFlapIndicator.h"
#include "UARTStateExchange.h"
#include "VarioOut.h"
#include "cmd/LedCmd.h"
#include "cmd/VarioCmd.h"
#include "FrontSeatVarioHandler.h"

LedMapping leds {.led1 = mbed::DigitalOut(D3),
				 .led2 = mbed::DigitalOut(D4),
				 .led3 = mbed::DigitalOut(D5),
				 .led4 = mbed::DigitalOut(D6),
				 .led5 = mbed::DigitalOut(D9),
				 .ledL = mbed::DigitalOut(D10)};

// TODO change
mbed::DigitalOut varioLedPin(D13);
mbed::DigitalOut varioPin(D11);

VarioOut vario(varioPin, varioLedPin);

DIOFlapIndicator indicator(leds);
UARTStateReceiver comm(PA_10);

LedCmdParser ledParser(indicator, vario);
VarioCmdParser varioParser(vario);

FrontSeatVarioHandler varioBtn(comm, A3);

rtos::Thread thread;

int main(void)
{
	comm.registerCmd(&ledParser);
	comm.registerCmd(&varioParser);

	thread.start(mbed::callback(&comm, &Runnable::run));

	while (true) {
		varioBtn.run();
		ThisThread::sleep_for(250ms);
	}

	return 0;
}
