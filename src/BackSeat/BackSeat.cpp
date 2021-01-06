#include "BackSeat.h"

#include "cmd/LedCmd.h"

BackSeat::BackSeat(AbstractFlapPosReader &reader, AbstractFlapIndicator &indicator, AbstractCmdSender &comm,
				   AbstractVarioHandler &vario)
	: Runnable(), reader(reader), indicator(indicator), comm(comm), vario(vario)
{
}

void BackSeat::run()
{
	flapState_t newState = reader.currentState();
	currentState		 = newState;

	indicator.updateState(currentState);

	LedCmd led(newState);
	comm.sendCmd(led);

	vario.run();
}