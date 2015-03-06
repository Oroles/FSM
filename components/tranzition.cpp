#include "tranzition.h"

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