#include "tranzition.h"

#include "../utils/utils.h"

State Tranzition::operator()(const State& s)
{
	if ( source == s )
	{
		return destination;
	}
	return source;
}

bool Tranzition::isAvailable(const State& s) const
{
	return s == source;
}

void Tranzition::setGuards(const std::vector<Expression>& g)
{
	display(DebugMessagePriority::Priority::Level1, "There are: ", g.size(), " expressions added to ", *this, "\n");
	guards = g;
}

std::ostream& operator<<(std::ostream& o, const Tranzition& t)
{
	o << "Tranzition: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}