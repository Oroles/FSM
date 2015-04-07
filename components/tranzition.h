#ifndef _TRANZITION_H_
#define _TRANZITION_H_

#include <vector>
#include <string>
#include <iostream>

#include "state.h"
#include "../expressions/expression.h"
#include "../expressions/sync.h"

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
	void setSync( const Sync s);
	void setExpressionModuleNames( const std::string name);

	State operator()(const State&);
	friend std::ostream& operator<<(std::ostream& o, const Tranzition&);

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