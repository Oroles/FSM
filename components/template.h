#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

#include "location.h"
#include "edge.h"
#include "observer.h"

class Template
{
public:
	Template();
	Template(const Template& rhs);
	Template(Template&& rhs);
	const Template& operator=(const Template& rhs);

	void addTransition( const Edge& t );
	TransitionAvailableStatus availableTransition(const Edge* t);
	void advance(Edge* t);
	void resetStepFlag();

	void setCurrentState( const Location& s );
	void setName( const std::string n );
	void setObserver(Observer*);
	std::string getName() const;

	void step();

	std::vector<Edge>::iterator begin();
	std::vector<Edge>::iterator end();

private:
	enum class StepStatus : int { NotAdvance, NotPossible, NormalAdvance, ChannelAdvance };
	/*
	* NotAdvance is when the template is not yet taken in consideration
	* NotPossible when the template iterates all over the transitions and doesn't find any available
	* NormalAdvance when template advanced without needing to be sync
	* ChannelAdvance when template advance because it had to sync with another one
	*/
	std::vector<Edge> transitions;
	Location currLocation;
	std::string name;

	Observer* obs;
	StepStatus stepStatus = StepStatus::NotAdvance;
};

#endif