#include "tranzition.h"

#include "../utils/utils.h"

State Tranzition::operator()(const State& s)
{
	//if ( this->isAvailable(s) )
	//{
		return destination;
	//}
	//return source;
}

bool Tranzition::isAvailable(const State& s) const
{
	if ( !(s == source) )
	{
		return false;
	}
	for ( auto& g : guards )
	{
		if ( !g.evaluate() )
		{
			return false;
		}
	}
	return true;
}

void Tranzition::setGuards(const std::vector<Expression>& g)
{
	display(DebugMessagePriority::Priority::Level1, "There are: ", g.size(), " guards added to ", *this, "\n");
	guards = g;
}

std::ostream& operator<<(std::ostream& o, const Tranzition& t)
{
	o << "Tranzition: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}