#include "template.h"

bool compareFunction( const Edge& lhs, const Edge& rhs )
{
	if ( lhs.hasSync() == true )
	{
		return true;
	}
	else
	{
		return false;
	}
}

Template::Template()
{
}

Template::Template(const Template& rhs): transitions(rhs.transitions), currLocation(rhs.currLocation), name(rhs.name)
{
}

Template::Template(Template&& rhs) : transitions(std::move(rhs.transitions)),
							   currLocation(std::move(rhs.currLocation)), name(std::move(rhs.name))
{
}

const Template& Template::operator=(const Template& rhs)
{
	transitions = rhs.transitions;
	currLocation = rhs.currLocation;
	name = rhs.name;
	return *this;
}

void Template::addTransition(const Edge& t)
{
	display(DebugMessagePriority::Template, "Edge: ", t, "is added to template: ", name, "\n");
	transitions.push_back( t );
	std::sort(transitions.begin(),transitions.end(),compareFunction);
}

TransitionAvailableStatus Template::availableTransition(const Edge* t)
{
	if ( stepStatus == StepStatus::NotAdvance )
	{
		return t->isAvailable(currLocation);
	}
	return TransitionAvailableStatus::NotSource;
}

void Template::advance(Edge* t)
{
	display(DebugMessagePriority::Template,"Advance Current location: ", currLocation, "for template ", name, "\n" );
	currLocation = t->operator()( currLocation );
	display(DebugMessagePriority::Template,"Advance New location: ", currLocation, "for template ", name, "\n" );
	stepStatus = StepStatus::ChannelAdvance;
}

void Template::setCurrentState(const Location& s)
{
	display(DebugMessagePriority::Template, "Init location: ", s, "is added to template: ", name, "\n");
	currLocation = s;
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

void Template::setObserver( Observer* obs)
{
	this->obs = obs;
}

std::string Template::getName() const
{
	return name;
}

void Template::resetStepFlag()
{
	stepStatus = StepStatus::NotAdvance;
}

std::vector<Edge>::iterator Template::begin()
{
	return transitions.begin();
}

std::vector<Edge>::iterator Template::end()
{
	return transitions.end();
}

void Template::step()
{
	if ( stepStatus != StepStatus::NotAdvance )
	{
		return;
	}

	for( auto& t : transitions )
	{
		TransitionAvailableStatus status = t.isAvailable( currLocation );
		if ( status == TransitionAvailableStatus::Available )
		{
			if ( t.hasSync() == true )
			{
				if ( obs->isAvailable(*this, t, t.getChannelName() ) == true )
				{
					display(DebugMessagePriority::Template,"Current location: ", currLocation, "for template ", name, "\n" );
					currLocation = t( currLocation );
					display(DebugMessagePriority::Template,"New location: ", currLocation, "for template ", name, "\n" );
					stepStatus = StepStatus::NormalAdvance;
					return;
				}
			}
			else
			{
				display(DebugMessagePriority::Template,"Current location: ", currLocation, "for template ", name, "\n" );
				currLocation = t( currLocation );
				display(DebugMessagePriority::Template,"New location: ", currLocation, "for template ", name, "\n" );
				stepStatus = StepStatus::NormalAdvance;
				return;
			}
		}
	}
	display(DebugMessagePriority::Template,"No transition available from the location ", currLocation, " for template ", name, "\n" );
}
