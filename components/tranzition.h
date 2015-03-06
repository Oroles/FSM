#ifndef _TRANZITION_H_
#define _TRANZITION_H_

#include <vector>

#include "state.h"

class Tranzition
{
public:
	Tranzition() : source(""), destination("")
	{

	}

	Tranzition(const State s, const State d) : source(s), destination(d)
	{

	}
	Tranzition(const Tranzition& rhs) : source(rhs.source), destination(rhs.destination)
	{

	}

	Tranzition& operator=(const Tranzition& rhs)
	{
		source = rhs.source;
		destination = rhs.destination;
		return *this;
	}

	State getSource() const
	{
		return source;
	}

	void setSource( const State s )
	{
		source = s;
	}

	State getDestination() const
	{
		return destination;
	}

	void setDestination( const State d )
	{
		destination = d;
	}

	State operator()(const State&);
	bool isAvailable(const State&) const;

private:
	State source;
	State destination;
};

#endif