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

std::ostream& operator<<(std::ostream& o, const Tranzition& t)
{
	o << "Tranzition: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}