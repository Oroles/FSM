#ifndef _TRANSITION_H_
#define _TRANSITION_H_

#include <vector>
#include <string>
#include <iostream>
#include <memory>

#include "location.h"
#include "../expressions/expression.h"
#include "../utils/utils.h"

class Edge
{
public:
	enum class TransitionAvailableStatus : int { Available, NotGuard, NotSource };

	Edge();

	Edge(const Location s, const Location d);
	Edge(const Edge& rhs);
	Edge(Edge&& rhs);

	const Edge& operator=(const Edge& rhs);
	Location getSource() const;
	void setSource( const Location s );
	Location getDestination() const;
	void setDestination( const Location d );
	void setSync( const std::string s);
	void setExpressionTemplateNames( const std::string name);

	Location operator()(const Location&);
	friend std::ostream& operator<<(std::ostream& o, const Edge&);

	TransitionAvailableStatus isAvailable(const Location&) const;
	bool hasSync() const;
	std::string getChannelName() const;

	void addGuard( const Expression& e );
	void addUpdate( const Expression& e );
	void addSelect( const std::string name );

private:
	Location source;
	Location destination;
	std::vector<Expression> guards;
	std::vector<Expression> updates;
	std::vector<std::string> selects;
	std::string sync;
};

#endif