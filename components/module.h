#ifndef _MODULE_H_
#define _MODULE_H_

#include <vector>
#include <string>

#include "state.h"
#include "transition.h"

class Module
{
public:
	Module();
	Module(const Module& rhs);
	Module(Module&& rhs);
	Module& operator=(const Module& rhs);

	void addTransition( const Transition& t );
	void setCurrentState( const State& s );

	void setName( const std::string n );
	std::string getName() const;

	State nextState( const State& s ) const;
	void step();
	void run();

private:
	std::vector<Transition> transitions;
	State currState;
	std::string name;
};

#endif