#include "fsm.h"

void FSM::step()
{
	for ( auto m : modules )
	{
		m.step();
	}
}