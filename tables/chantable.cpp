#include "chantable.h"

ChanTable& ChanTable::getInstance()
{
	static ChanTable instance;
	return instance;
}

ChanTable::ChanTable()
{

}

void ChanTable::addEntry(const Chan& c)
{
	table[c.getName()] = c;
}

void ChanTable::addEntries(const std::vector<Chan>& v)
{
	for ( auto& c : v )
	{
		table[c.getName()] = c;
	}
}