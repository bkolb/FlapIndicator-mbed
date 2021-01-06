#pragma once

#include "Runnable.h"
#include "StateTypes.h"

class AbstractVarioHandler : public Runnable
{
  public:
	virtual void handleVarioButtonPressed() = 0;

	void run() override;
};