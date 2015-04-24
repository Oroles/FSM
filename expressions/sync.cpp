#include "sync.h"

#include "../tables/chantable.h"

#include <cassert>
#include <algorithm>

Sync::Sync() : name("")
{

}

Sync::Sync(const std::string& n) : name(n)
{
	
}

Sync::Sync(const Sync& rhs) : name(rhs.name)
{
	
}
	
Sync::Sync(Sync&& rhs) : name(std::move(rhs.name))
{

}

Sync& Sync::operator=(const Sync& rhs)
{
	name = rhs.name;
	return *this;
}

bool Sync::isSync() const
{	
	if ( name == "" )
	{
		return true;
	}
	
	const char type = name.back();
	const std::string chan = name.substr(0,name.length()-1);
	if ( type == '!' )
	{
		ChanTable::getInstance().wantSender( chan );
		return ChanTable::getInstance().isSenderSync( chan );
	}
	else
	{
		ChanTable::getInstance().wantReceiver( chan );
		return ChanTable::getInstance().isReceiverSync( chan );
	}
	return false;
}

void Sync::deSync()
{
	if ( name == "" )
	{
		return;
	}
	const char type = name.back();
	const std::string chan = name.substr(0,name.length()-1);
	if ( type == '!' )
	{
		ChanTable::getInstance().refuseSender( chan );
	}
	else
	{
		ChanTable::getInstance().refuseReceiver( chan );
	}
	return;
}

std::ostream& operator<<( std::ostream& o, const Sync& s )
{
	o << "Sync: " << s.name;
	return o;
}