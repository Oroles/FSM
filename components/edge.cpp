#include "edge.h"

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/pintable.h"

Edge::Edge() : source(""), destination(""), sync("")
{

}

Edge::Edge(const Location s, const Location d) : source(s), destination(d)
{
	assert(s.getName().size() != 0);
	assert(d.getName().size() != 0);
}

Edge::Edge(const Edge& rhs) : source(rhs.source), destination(rhs.destination), 
												guards(rhs.guards), updates(rhs.updates), selects(rhs.selects),
												sync(rhs.sync)
{
	assert(rhs.source.getName().size() != 0);
	assert(rhs.destination.getName().size() != 0);
}

Edge::Edge(Edge&& rhs) : source(std::move(rhs.source)), destination(std::move(rhs.destination)),
										   guards(std::move(rhs.guards)), updates(std::move(rhs.updates)),
										   selects(std::move(rhs.selects)), sync(std::move(rhs.sync))
{

}

const Edge& Edge::operator=(const Edge& rhs)
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

Location Edge::getSource() const
{
	return source;
}

void Edge::setSource( const Location s )
{
	source = s;
}

Location Edge::getDestination() const
{
	return destination;
}

void Edge::setDestination( const Location d )
{
	destination = d;
}

void Edge::setSync(const std::string s)
{
	display(DebugMessagePriority::Edge, "There is: ", s, " sync added to ", *this, "\n" );
	sync = s;
}

void Edge::setExpressionTemplateNames( const std::string name)
{
	display(DebugMessagePriority::Edge, "Edge ", *this, "is part of the template ", name, "\n" );
	for ( auto& g : guards )
	{
		g.setSystemName(name);
	}
	for ( auto& u : updates )
	{
		u.setSystemName(name);
	}
}

Location Edge::operator()(const Location& s)
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

TransitionAvailableStatus Edge::isAvailable(const Location& s) const
{
	if ( s != source )
	{
		return TransitionAvailableStatus::NotSource;
	}
	for ( auto& g : guards )
	{
		if ( !g.evaluate() )
		{
			return TransitionAvailableStatus::NotGuard;
		}
	}
	return TransitionAvailableStatus::Available;
}

bool Edge::hasSync() const
{
	return sync != "";
}

std::string Edge::getChannelName() const
{
	return sync;
}

void Edge::addGuard( const Expression& e )
{
	display(DebugMessagePriority::Edge, "The guard ", e, "is added to ", *this, "\n");
	guards.push_back( e );
}

void Edge::addUpdate( const Expression& e )
{
	display(DebugMessagePriority::Edge, "The update ", e, "is added to ", *this, "\n");
	updates.push_back( e );
}

void Edge::addSelect( const std::string name )
{
	display(DebugMessagePriority::Edge, "The select ", name, "is added to ", *this, "\n" );
	selects.push_back( name );
}

std::ostream& operator<<(std::ostream& o, const Edge& t)
{
	o << "Edge: " << t.source.getName() << " -> " << t.destination.getName();
	return o;
}