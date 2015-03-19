#include "clocktable.h"

ClockTable& ClockTable::getInstance()
{
	static ClockTable instance;
	return instance;
}

ClockTable::ClockTable()
{

}

void ClockTable::addEntry(const Clock& c)
{
	table[c.getName()] = c;
}

void ClockTable::addEntries(const std::vector<Clock>& v)
{
	for ( auto& c : v )
	{
		table[c.getName()] = c;
	}
}

int ClockTable::getValue(const std::string name)
{
	return table[name].getValue();
}

void ClockTable::setValue(const std::string name, int value)
{
	table[name].setValue(value);
}

void ClockTable::updateClocks()
{
	for ( auto& c : table)
	{
		c.second.update();
	}
}

bool ClockTable::exists(const std::string name) const
{
	auto it = table.find(name);
	return it != table.end();
}