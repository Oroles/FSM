#include "tranzition.h"

#include "../utils/utils.h"

Tranzition::Tranzition() : source(""), destination("")
{

}

Tranzition::Tranzition(const State s, const State d) : source(s), destination(d)
{
	assert(s.getName().size() != 0);
	assert(d.getName().size() != 0);
}
Tranzition::Tranzition(const Tranzition& rhs) : source(rhs.source), destination(rhs.destination), guards(rhs.guards)
{
	assert(rhs.source.getName().size() != 0);
	assert(rhs.destination.getName().size() != 0);
}

Tranzition& Tranzition::operator=(const Tranzition& rhs)
{
	assert(rhs.source.getName().size() != 0 );
	assert(rhs.destination.getName().size() != 0 );
	source = rhs.source;
	destination = rhs.destination;
	guards = rhs.guards;
	return *this;
}

State Tranzition::getSource() const
{
	return source;
}

void Tranzition::setSource( const State s )
{
	assert(s.getName().size() != 0 );
	source = s;
}

State Tranzition::getDestination() const
{
	return destination;
}

void Tranzition::setDestination( const State d )
{
	assert(d.getName().size() != 0 );
	destination = d;
}

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
	display(DebugMessagePriority::Tranzition, "There are: ", g.size(), " guards added to ", *this, "\n");
	guards = g;
}

std::ostream& operator<<(std::ostream& o, const Tranzition& t)
{
	o << "Tranzition: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}