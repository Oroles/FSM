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

bool ChanTable::existsEntry(const Chan& c)
{
	return table.find(c.getName()) != table.end();
}

bool ChanTable::isSenderSync(std::string name)
{
	return table[name].isSenderSync();
}

bool ChanTable::isReceiverSync(std::string name)
{
	return table[name].isReceiverSync();
}

void ChanTable::wantSender(std::string name)
{
	table[name].wantSender();
}

void ChanTable::wantReceiver(std::string name)
{
	table[name].wantReceiver();
}