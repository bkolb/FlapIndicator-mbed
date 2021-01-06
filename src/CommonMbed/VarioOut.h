#pragma once

#include "AbstractVarioOut.h"
#include "DigitalOut.h"

class VarioOut : public AbstractVarioOut
{
	DigitalOut &out;

  public:
	VarioOut(DigitalOut &out) : out(out) {}

	bool isVario() override { return out.read(); };

	virtual void setVario(bool v) override { out.write(v); }
};