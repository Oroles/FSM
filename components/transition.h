#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include <vector>
#include <string>
#include <iostream>

#include "state.h"
#include "../expressions/expression.h"
#include "../expressions/sync.h"

class Transition
{
public:
	Transition();

	Transition(const State s, const State d);
	Transition(const Transition& rhs);
	Transition(Transition&& rhs);

	Transition& operator=(const Transition& rhs);
	State getSource() const;
	void setSource( const State s );
	State getDestination() const;
	void setDestination( const State d );
	void setSync( const Sync s);
	void setExpressionTemplateNames( const std::string name);

	State operator()(const State&);
	friend std::ostream& operator<<(std::ostream& o, const Transition&);

	bool isAvailable(const State&) const;
	bool isSync() const;

	void addGuard( const Expression& e );
	void addUpdate( const Expression& e );
	void addSelect( const std::string name );

private:
	State source;
	State destination;
	std::vector<Expression> guards;
	std::vector<Expression> updates;
	std::vector<std::string> selects;
	Sync sync;

};

#endif