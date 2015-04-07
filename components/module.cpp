#include "module.h"
#include "../utils/utils.h"

Module::Module()
{
}

Module::Module(const Module& rhs): tranzitions(rhs.tranzitions), currState(rhs.currState), name(rhs.name)
{
}

Module::Module(Module&& rhs) : tranzitions(std::move(rhs.tranzitions)),
							   currState(std::move(rhs.currState)), name(std::move(rhs.name))
{
}

Module& Module::operator=(const Module& rhs)
{
	tranzitions = rhs.tranzitions;
	currState = rhs.currState;
	name = rhs.name;
	return *this;
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
	for ( auto& t : tranzitions )
	{
		t.setExpressionModuleNames( n );
	}
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
