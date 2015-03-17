#include "module.h"
#include "../utils/utils.h"

Module::Module()
{
}

Module::Module(const Module& rhs): states(rhs.states), tranzitions(rhs.tranzitions), currState(rhs.currState), name(rhs.name)
{
}

void Module::addState(const State& s)
{
	display(DebugMessagePriority::Module, "State: ", s, "is added to module: ", name, "\n");
	states.push_back( s );
}

void Module::addTranzition(const Tranzition& t)
{
	display(DebugMessagePriority::Module, "Tranzition: ", t, "is added to module: ", name, "\n");
	tranzitions.push_back( t );
}

void Module::setCurrentState(const State& s)
{
	display(DebugMessagePriority::Module, "Init state: ", s, "is added to module: ", name, "\n");
	currState = s;
}

void Module::setName(const std::string n)
{
	assert(n.size() != 0);
	display(DebugMessagePriority::Module, "Set name to module: ", n, "\n");
	name = n;
}

std::string Module::getName() const
{
	return name;
}

State Module::nextState(const State& s) const
{
	for( auto& t : tranzitions )
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
	for( auto& t : tranzitions )
	{
		if ( t.isAvailable( currState ) )
		{
			display(DebugMessagePriority::Module,"Current state: ", currState, "for module ", name, "\n" );
			currState = t( currState );
			display(DebugMessagePriority::Module,"New state: ", currState, "for module ", name, "\n" );
			return;
		}
	}
	display(DebugMessagePriority::Module,"No tranzition available from the state ", currState, " for module ", name, "\n" );
}

void Module::run()
{
	while( 1 ) {
		this->step();
	}
}
