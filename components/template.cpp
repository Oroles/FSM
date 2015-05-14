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

Edge::TransitionAvailableStatus Template::availableTransition(const Edge* t)
{
	if ( stepStatus == StepStatus::NotAdvance )
	{
		return t->isAvailable(currLocation);
	}
	return Edge::TransitionAvailableStatus::NotSource;
}

void Template::channelAdvance(Edge* t)
{
	display(DebugMessagePriority::Template,"Advance Current location: ", currLocation, "for template ", name, "\n" );
	currLocation = t->operator()( currLocation );
	display(DebugMessagePriority::Template,"Advance New location: ", currLocation, "for template ", name, "\n" );
	stepStatus = StepStatus::ChannelAdvance;
}

void Template::normalAdvance(Edge* t)
{
	display(DebugMessagePriority::Template,"Current location: ", currLocation, "for template ", name, "\n" );
	currLocation = t->operator()( currLocation );
	display(DebugMessagePriority::Template,"New location: ", currLocation, "for template ", name, "\n" );
	stepStatus = StepStatus::NormalAdvance;
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

bool Template::step()
{
	if ( stepStatus != StepStatus::NotAdvance )
	{
		return false;
	}

	for( auto& t : transitions )
	{
		Edge::TransitionAvailableStatus status = t.isAvailable( currLocation );
		if ( status == Edge::TransitionAvailableStatus::Available )
		{
			if ( t.hasSync() == true )
			{
				if ( obs->isAvailable(*this, t, t.getChannelName() ) == true )
				{
					this->normalAdvance(&t);
					if ( ( currLocation.getType() == "committed" ) || ( currLocation.getType() == "urgent" ) )
					{
						/* if the state is committed it has to move from the current location, therefore
						* reset the flag of the template, and try to make another step, if there is no
						* step available from the new state then throw an exception because it's a deadlock
						*/
						stepStatus = StepStatus::NotAdvance;
						bool returnFlag = this->step();
						if ( returnFlag == false )
						{
							throw DeadlockLocations();
						}
						stepStatus = StepStatus::NormalAdvance;
					}
					return true;
				}
			}
			else
			{
				this->normalAdvance(&t);
				if ( ( currLocation.getType() == "committed" ) || ( currLocation.getType() == "urgent" ) )
				{
					/* See the previous comment */
					stepStatus = StepStatus::NotAdvance;
					bool returnFlag = this->step();
					if ( returnFlag == false )
					{
						throw DeadlockLocations();
					}
					stepStatus = StepStatus::NormalAdvance;
				}
				return true;
			}
		}
	}
	display(DebugMessagePriority::Template,"No transition available from the location ", currLocation, " for template ", name, "\n" );
	return false;
}
