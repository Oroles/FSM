#include "sync.h"

#include "../tables/symboltable.h"

#include <cassert>
#include <algorithm>

Sync::Sync() : name("")
{

}

Sync::Sync(const std::string& n) : name(n)
{
	//assert( name != "" );
	//assert( name.end() != std::find_if(name.begin(),name.end(),[](char c){ return ( c == '?' || c == '!' ); }));
}

Sync::Sync(const Sync& rhs) : name(rhs.name), lastAction(rhs.lastAction)
{
	//assert( name != "" );	
}
	
Sync::Sync(Sync&& rhs) : name(std::move(rhs.name)), lastAction(std::move(rhs.lastAction))
{
	assert( name != "" );
}

Sync& Sync::operator=(const Sync& rhs)
{
	name = rhs.name;
	lastAction = rhs.lastAction;
	return *this;
}

bool Sync::isSync()
{
	return false;
}

std::ostream& operator<<( std::ostream& o, const Sync& s )
{
	o << "Sync: " << s.name;
	return o;
}