#include "tranzition.h"

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/pintable.h"

Tranzition::Tranzition() : source(""), destination(""), sync("")
{

}

Tranzition::Tranzition(const State s, const State d) : source(s), destination(d)
{
	assert(s.getName().size() != 0);
	assert(d.getName().size() != 0);
}
Tranzition::Tranzition(const Tranzition& rhs) : source(rhs.source), destination(rhs.destination), 
												guards(rhs.guards), updates(rhs.updates), selects(rhs.selects),
												sync(rhs.sync)
{
	assert(rhs.source.getName().size() != 0);
	assert(rhs.destination.getName().size() != 0);
}

Tranzition::Tranzition(Tranzition&& rhs) : source(std::move(rhs.source)), destination(std::move(rhs.destination)),
										   guards(std::move(rhs.guards)), updates(std::move(rhs.updates)),
										   selects(std::move(rhs.selects)), sync(std::move(rhs.sync))
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
	selects = rhs.selects;
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

void Tranzition::setSync(const Sync s)
{
	display(DebugMessagePriority::Tranzition, "There is: ", s, " sync added to ", *this, "\n" );
	sync = s;
}

void Tranzition::setExpressionModuleNames( const std::string name)
{
	display(DebugMessagePriority::Tranzition, "Tranzition ", *this, "is part of the module ", name, "\n" );
	for ( auto& g : guards )
	{
		g.setModuleName(name);
	}
	for ( auto& u : updates )
	{
		u.setModuleName(name);
	}
}

State Tranzition::operator()(const State& s)
{
	for ( auto& s : selects )
	{
		PinTable::getInstance().updateEntry( s );
	}

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
	if ( !this->isSync() )
	{
		return false;
	}
	return true;
}

bool Tranzition::isSync() const
{
	return sync.isSync();
}

void Tranzition::addGuard( const Expression& e )
{
	display(DebugMessagePriority::Tranzition, "The guard ", e, "is added to ", *this, "\n");
	guards.push_back( e );
}

void Tranzition::addUpdate( const Expression& e )
{
	display(DebugMessagePriority::Tranzition, "The update ", e, "is added to ", *this, "\n");
	updates.push_back( e );
}

void Tranzition::addSelect( const std::string name )
{
	display(DebugMessagePriority::Tranzition, "The select ", name, "is added to ", *this, "\n" );
	selects.push_back( name );
}

std::ostream& operator<<(std::ostream& o, const Tranzition& t)
{
	o << "Tranzition: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}