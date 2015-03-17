#ifndef _MODULE_H_
#define _MODULE_H_

#include <vector>
#include <string>

#include "state.h"
#include "tranzition.h"

class Module
{
public:
	Module();
	Module(const Module& rhs);
	Module(Module&& rhs);
	Module& operator=(const Module& rhs);

	void addState( const State& s );
	void addTranzition( const Tranzition& t );
	void setCurrentState( const State& s );

	void setName( const std::string n );
	std::string getName() const;

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