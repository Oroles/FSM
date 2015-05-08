#include "transition.h"

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/pintable.h"

Transition::Transition() : source(""), destination(""), sync("")
{

}

Transition::Transition(const Location s, const Location d) : source(s), destination(d)
{
	assert(s.getName().size() != 0);
	assert(d.getName().size() != 0);
}
Transition::Transition(const Transition& rhs) : source(rhs.source), destination(rhs.destination), 
												guards(rhs.guards), updates(rhs.updates), selects(rhs.selects),
												sync(rhs.sync)
{
	assert(rhs.source.getName().size() != 0);
	assert(rhs.destination.getName().size() != 0);
}

Transition::Transition(Transition&& rhs) : source(std::move(rhs.source)), destination(std::move(rhs.destination)),
										   guards(std::move(rhs.guards)), updates(std::move(rhs.updates)),
										   selects(std::move(rhs.selects)), sync(std::move(rhs.sync))
{

}

const Transition& Transition::operator=(const Transition& rhs)
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

Location Transition::getSource() const
{
	return source;
}

void Transition::setSource( const Location s )
{
	assert(s.getName().size() != 0 );
	source = s;
}

Location Transition::getDestination() const
{
	return destination;
}

void Transition::setDestination( const Location d )
{
	assert(d.getName().size() != 0 );
	destination = d;
}

void Transition::setSync(const std::string s)
{
	display(DebugMessagePriority::Transition, "There is: ", s, " sync added to ", *this, "\n" );
	sync = s;
}

void Transition::setExpressionTemplateNames( const std::string name)
{
	display(DebugMessagePriority::Transition, "Transition ", *this, "is part of the template ", name, "\n" );
	for ( auto& g : guards )
	{
		g.setSystemName(name);
	}
	for ( auto& u : updates )
	{
		u.setSystemName(name);
	}
}

Location Transition::operator()(const Location& s)
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

TranzactionAvailableStatus Transition::isAvailable(const Location& s) const
{
	if ( s != source )
	{
		return TranzactionAvailableStatus::NotSource;
	}
	for ( auto& g : guards )
	{
		if ( !g.evaluate() )
		{
			return TranzactionAvailableStatus::NotGuard;
		}
	}
	return TranzactionAvailableStatus::Available;
}

bool Transition::hasSync() const
{
	return sync != "";
}

std::string Transition::getChannelName() const
{
	return sync;
}

void Transition::addGuard( const Expression& e )
{
	display(DebugMessagePriority::Transition, "The guard ", e, "is added to ", *this, "\n");
	guards.push_back( e );
}

void Transition::addUpdate( const Expression& e )
{
	display(DebugMessagePriority::Transition, "The update ", e, "is added to ", *this, "\n");
	updates.push_back( e );
}

void Transition::addSelect( const std::string name )
{
	display(DebugMessagePriority::Transition, "The select ", name, "is added to ", *this, "\n" );
	selects.push_back( name );
}

std::ostream& operator<<(std::ostream& o, const Transition& t)
{
	o << "Transition: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}