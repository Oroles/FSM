#include "template.h"
#include "../utils/utils.h"

Template::Template()
{
}

Template::Template(const Template& rhs): transitions(rhs.transitions), currState(rhs.currState), name(rhs.name)
{
}

Template::Template(Template&& rhs) : transitions(std::move(rhs.transitions)),
							   currState(std::move(rhs.currState)), name(std::move(rhs.name))
{
}

Template& Template::operator=(const Template& rhs)
{
	transitions = rhs.transitions;
	currState = rhs.currState;
	name = rhs.name;
	return *this;
}

void Template::addTransition(const Transition& t)
{
	display(DebugMessagePriority::Template, "Transition: ", t, "is added to template: ", name, "\n");
	transitions.push_back( t );
}

void Template::setCurrentState(const State& s)
{
	display(DebugMessagePriority::Template, "Init state: ", s, "is added to template: ", name, "\n");
	currState = s;
}

void Template::setName(const std::string n)
{
	assert(n.size() != 0);
	display(DebugMessagePriority::Template, "Set name to template: ", n, "\n");
	name = n;
	for ( auto& t : transitions )
	{
		t.setExpressionTemplateNames( n );
	}
}

std::string Template::getName() const
{
	return name;
}

State Template::nextState(const State& s) const
{
	for( auto& t : transitions )
	{
		if ( t.isAvailable( s ) )
		{
			return t.getDestination();
		}
	}
	return s;		
}

void Template::step()
{
	for( auto& t : transitions )
	{
		if ( t.isAvailable( currState ) )
		{
			display(DebugMessagePriority::Template,"Current state: ", currState, "for template ", name, "\n" );
			currState = t( currState );
			display(DebugMessagePriority::Template,"New state: ", currState, "for template ", name, "\n" );
			return;
		}
	}
	display(DebugMessagePriority::Template,"No transition available from the state ", currState, " for template ", name, "\n" );
}

void Template::run()
{
	while( 1 ) {
		this->step();
	}
}
