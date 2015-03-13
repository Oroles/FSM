#ifndef _TRANZITION_H_
#define _TRANZITION_H_

#include <vector>
#include <iostream>

#include "state.h"
#include "./expressions/expression.h"

class Tranzition
{
public:
	Tranzition() : source(""), destination("")
	{

	}

	Tranzition(const State s, const State d) : source(s), destination(d)
	{
		assert(s.getName().size() != 0);
		assert(d.getName().size() != 0);
	}
	Tranzition(const Tranzition& rhs) : source(rhs.source), destination(rhs.destination), guards(rhs.guards)
	{
		assert(rhs.source.getName().size() != 0);
		assert(rhs.destination.getName().size() != 0);
	}

	Tranzition& operator=(const Tranzition& rhs)
	{
		assert(rhs.source.getName().size() != 0 );
		assert(rhs.destination.getName().size() != 0 );
		source = rhs.source;
		destination = rhs.destination;
		guards = rhs.guards;
		return *this;
	}

	State getSource() const
	{
		return source;
	}

	void setSource( const State s )
	{
		assert(s.getName().size() != 0 );
		source = s;
	}

	State getDestination() const
	{
		return destination;
	}

	void setDestination( const State d )
	{
		assert(d.getName().size() != 0 );
		destination = d;
	}

	void setGuards( const std::vector<Expression>& g );
	State operator()(const State&);
	friend std::ostream& operator<<(std::ostream& o, const Tranzition&);
	bool isAvailable(const State&) const;

private:
	State source;
	State destination;
	std::vector<Expression> guards;
};

#endif