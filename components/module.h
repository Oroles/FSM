#ifndef _MODULE_H_
#define _MODULE_H_

#include <vector>

#include "state.h"
#include "tranzition.h"
#include "../utils/utils.h"

class Module
{
public:
	Module()
	{

	}

	Module(const Module& rhs) : states(rhs.states), tranzitions(rhs.tranzitions), currState(rhs.currState)
	{
	}

	void addState( const State& s )
	{
		display(DebugMessagePriority::Priority::Level1, "State: ", s, "is added to module\n");
		states.push_back( s );
	}

	void addTranzition( const Tranzition& t )
	{
		display(DebugMessagePriority::Priority::Level1, "Tranzaction: ", t, "is added to module\n");
		tranzitions.push_back( t );
	}
	void setCurrentState( const State& s )
	{
		currState = s;
	}

	State nextState( const State& s ) const;
	void step();
	void run();

private:
	std::vector<State> states;
	std::vector<Tranzition> tranzitions;
	State currState;
};

#endif