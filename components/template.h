#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <vector>
#include <string>

#include "state.h"
#include "transition.h"

class Template
{
public:
	Template();
	Template(const Template& rhs);
	Template(Template&& rhs);
	Template& operator=(const Template& rhs);

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