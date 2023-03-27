#pragma once

#include "AbstractVarioOut.h"
#include "DigitalOut.h"

class VarioOut : public AbstractVarioOut
{
	DigitalOut &out;
	DigitalOut &led;

  public:
	VarioOut(DigitalOut &out, DigitalOut &led) : out(out),led(led) {}

	bool isVario() override { return out.read(); };

	virtual void setVario(bool v) override {
		//led = !led;
		//out = !out;

		led = v;
		out = v;

		/*if(v) {
			out = 0;
		} else {
			out = 1;
		}
		*/
	}
};