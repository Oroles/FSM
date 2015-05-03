#include "chantable.h"

ChanTable& ChanTable::getInstance()
{
	static ChanTable instance;
	return instance;
}

ChanTable::ChanTable()
{

}

void ChanTable::addEntries(const std::vector<std::shared_ptr<Chan> >& v)
{
	for ( auto& c : v )
	{
		table[c->getName()] = c;
	}
}

Chan::ChanType ChanTable::getType(std::string name)
{
	return table[name]->getType();
}

bool ChanTable::existsEntry(const std::string& name)
{
	return table.find(name) != table.end();
}

bool ChanTable::isSenderSync(std::string name)
{
	return table[name]->isSenderSync();
}

bool ChanTable::isReceiverSync(std::string name)
{
	return table[name]->isReceiverSync();
}