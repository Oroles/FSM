#include "tranzition.h"

#include "../utils/utils.h"
#include "symboltable.h"

Tranzition::Tranzition() : source(""), destination("")
{

}

Tranzition::Tranzition(const State s, const State d) : source(s), destination(d)
{
	assert(s.getName().size() != 0);
	assert(d.getName().size() != 0);
}
Tranzition::Tranzition(const Tranzition& rhs) : source(rhs.source), destination(rhs.destination), guards(rhs.guards), updates(rhs.updates), sync(rhs.sync)
{
	assert(rhs.source.getName().size() != 0);
	assert(rhs.destination.getName().size() != 0);
}

Tranzition::Tranzition(Tranzition&& rhs) : source(std::move(rhs.source)), destination(std::move(rhs.destination)),
										   guards(std::move(rhs.guards)), updates(std::move(rhs.updates)),
										   sync(std::move(rhs.sync))
{

}

Tranzition& Tranzition::operator=(const Tranzition& rhs)
{
	assert(rhs.source.getName().size() != 0 );
	assert(rhs.destination.getName().size() != 0 );
	source = rhs.source;
	destination = rhs.destination;
	guards = rhs.guards;
	updates = rhs.updates;
	sync = rhs.sync;
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
	for ( auto& u : updates )
	{
		u.evaluate();
	}
	return destination;
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

void Tranzition::setUpdates(const std::vector<Expression>& u)
{
	display(DebugMessagePriority::Tranzition, "There are: ", u.size(), "updates added to ", *this, "\n" );
	updates = u;
}

void Tranzition::setSyncs(const std::vector<std::string>& s)
{
	display(DebugMessagePriority::Tranzition, "There are:", s.size(), " syncs added to ", *this, "\n" );
	sync = s;
}

std::ostream& operator<<(std::ostream& o, const Tranzition& t)
{
	o << "Tranzition: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}