#include "module.h"
#include "../utils/utils.h"

State Module::nextState(const State& s) const
{
	for( auto t : tranzitions )
	{
		if ( t.isAvailable( s ) )
		{
			return t.getDestination();
		}
	}
	return s;		
}

void Module::step()
{
	for( auto t : tranzitions )
	{
		if ( t.isAvailable( currState ) )
		{
			currState = t( currState );
			display(DebugMessagePriority::Priority::Level2,"New state: ", currState, "for module ", name ,"\n" );
			return;
		}
	}
	display(DebugMessagePriority::Priority::Level2,"No tranzition available for module ", name, " from the state ", currState, "\n" );
}

void Module::run()
{
	while( 1 ) {
		this->step();
	}
}
