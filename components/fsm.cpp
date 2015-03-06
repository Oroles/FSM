#include "fsm.h"

void FSM::step()
{
	for ( auto m : modules )
	{
		m.step();
	}
}

void FSM::startModules()
{
	for ( auto m : modules )
	{
		
	}
}