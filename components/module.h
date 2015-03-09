#ifndef _MODULE_H_
#define _MODULE_H_

#include <vector>
#include <string>

#include "state.h"
#include "tranzition.h"
#include "../utils/utils.h"

class Module
{
public:
	Module()
	{

	}

	Module(const Module& rhs) : states(rhs.states), tranzitions(rhs.tranzitions), currState(rhs.currState), name(rhs.name)
	{
	}

	void addState( const State& s )
	{
		display(DebugMessagePriority::Priority::Level1, "State: ", s, "is added to module: ", name, "\n");
		states.push_back( s );
	}

	void addTranzition( const Tranzition& t )
	{
		display(DebugMessagePriority::Priority::Level1, "Tranzition: ", t, "is added to module: ", name, "\n");
		tranzitions.push_back( t );
	}
	void setCurrentState( const State& s )
	{
		display(DebugMessagePriority::Priority::Level1, "Init state: ", s, "is added to module: ", name, "\n");
		currState = s;
	}

	void setName( const std::string n )
	{
		assert(n.size() != 0);
		display(DebugMessagePriority::Priority::Level1, "Set name to module: ", n, "\n");
		name = n;
	}

	State nextState( const State& s ) const;
	void step();
	void run();

private:
	std::vector<State> states;
	std::vector<Tranzition> tranzitions;
	State currState;
	std::string name;
};

#endif