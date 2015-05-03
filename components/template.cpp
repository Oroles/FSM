#include "template.h"

bool compareFunction( const Transition& lhs, const Transition& rhs )
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

Template::Template(const Template& rhs): transitions(rhs.transitions), currState(rhs.currState), name(rhs.name)
{
}

Template::Template(Template&& rhs) : transitions(std::move(rhs.transitions)),
							   currState(std::move(rhs.currState)), name(std::move(rhs.name))
{
}

const Template& Template::operator=(const Template& rhs)
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
	std::sort(transitions.begin(),transitions.end(),compareFunction);
}

TranzactionAvailableStatus Template::availableTransition(const Transition* t)
{
	if ( stepStatus == StepStatus::NotAdvance )
	{
		return t->isAvailable(currState);
	}
	return TranzactionAvailableStatus::NotSource;
}

void Template::advance(Transition* t)
{
	display(DebugMessagePriority::Template,"Advance Current state: ", currState, "for template ", name, "\n" );
	currState = t->operator()( currState );
	display(DebugMessagePriority::Template,"Advance New state: ", currState, "for template ", name, "\n" );
	stepStatus = StepStatus::ChannelAdvance;
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

std::vector<Transition>::iterator Template::begin()
{
	return transitions.begin();
}

std::vector<Transition>::iterator Template::end()
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
		TranzactionAvailableStatus status = t.isAvailable( currState );
		if ( status == TranzactionAvailableStatus::Available )
		{
			if ( t.hasSync() == true )
			{
				if ( obs->isAvailable(*this, t, t.getChannelName() ) == true )
				{
					display(DebugMessagePriority::Template,"Current state: ", currState, "for template ", name, "\n" );
					currState = t( currState );
					display(DebugMessagePriority::Template,"New state: ", currState, "for template ", name, "\n" );
					stepStatus = StepStatus::NormalAdvance;
					return;
				}
			}
			else
			{
				display(DebugMessagePriority::Template,"Current state: ", currState, "for template ", name, "\n" );
				currState = t( currState );
				display(DebugMessagePriority::Template,"New state: ", currState, "for template ", name, "\n" );
				stepStatus = StepStatus::NormalAdvance;
				return;
			}
		}
	}
	display(DebugMessagePriority::Template,"No transition available from the state ", currState, " for template ", name, "\n" );
}
