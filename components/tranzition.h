#ifndef _TRANZITION_H_
#define _TRANZITION_H_

#include <vector>
#include <iostream>

#include "state.h"
#include "../expressions/expression.h"

class Tranzition
{
public:
	Tranzition();

	Tranzition(const State s, const State d);
	Tranzition(const Tranzition& rhs);
	Tranzition(Tranzition&& rhs);

	Tranzition& operator=(const Tranzition& rhs);
	State getSource() const;
	void setSource( const State s );
	State getDestination() const;
	void setDestination( const State d );

	void setGuards( const std::vector<Expression>& g );
	void setUpdates( const std::vector<Expression>& u );
	void setSync( const std::string s);
	State operator()(const State&);
	friend std::ostream& operator<<(std::ostream& o, const Tranzition&);
	bool isAvailable(const State&) const;

private:
	State source;
	State destination;
	std::vector<Expression> guards;
	std::vector<Expression> updates;
	std::string sync;
};

#endif