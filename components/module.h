#ifndef _MODULE_H_
#define _MODULE_H_

#include <vector>

#include "state.h"
#include "tranzition.h"

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
		states.push_back( s );
	}

	void addTranzition( const Tranzition& t )
	{
		tranzitions.push_back( t );
	}
	void setCurrentState( const State& s )
	{
		currState = s;
	}

	State nextState( const State& s ) const;
	void step();

private:
	std::vector<State> states;
	std::vector<Tranzition> tranzitions;
	State currState;
};

#endif