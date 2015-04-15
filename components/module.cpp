#include "module.h"
#include "../utils/utils.h"

Module::Module()
{
}

Module::Module(const Module& rhs): transitions(rhs.transitions), currState(rhs.currState), name(rhs.name)
{
}

Module::Module(Module&& rhs) : transitions(std::move(rhs.transitions)),
							   currState(std::move(rhs.currState)), name(std::move(rhs.name))
{
}

Module& Module::operator=(const Module& rhs)
{
	transitions = rhs.transitions;
	currState = rhs.currState;
	name = rhs.name;
	return *this;
}

void Module::addTransition(const Transition& t)
{
	display(DebugMessagePriority::Module, "Transition: ", t, "is added to module: ", name, "\n");
	transitions.push_back( t );
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
	for ( auto& t : transitions )
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
	for( auto& t : transitions )
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
	for( auto& t : transitions )
	{
		if ( t.isAvailable( currState ) )
		{
			display(DebugMessagePriority::Module,"Current state: ", currState, "for module ", name, "\n" );
			currState = t( currState );
			display(DebugMessagePriority::Module,"New state: ", currState, "for module ", name, "\n" );
			return;
		}
	}
	display(DebugMessagePriority::Module,"No transition available from the state ", currState, " for module ", name, "\n" );
}

void Module::run()
{
	while( 1 ) {
		this->step();
	}
}
