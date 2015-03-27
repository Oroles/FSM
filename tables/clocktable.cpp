#include "clocktable.h"

#include <cassert>

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
	if ( !this->exists(c.getName()) )
	{
		table[c.getName()] = c;	
	}
	else
	{
		assert(!"Entry in clock table already exits");
	}
	
}

void ClockTable::addEntries(const std::vector<Clock>& v)
{
	for ( auto& c : v )
	{
		this->addEntry( c );
	}
}

int ClockTable::getValue(const std::string name)
{
	if ( this->exists(name) )
	{
		return table[name].getValue();
	}
	else
	{
		assert("!Entry in clock table doesn't exists");
	}
	return -1;
}

void ClockTable::setValue(const std::string name, int value)
{
	messages.push_back( std::pair<std::string,int>( name, value ) ); 
}

void ClockTable::updateClocks()
{
	for ( auto& c : table)
	{
		c.second.update();
	}
	for ( auto& p : messages )
	{
		if ( this->exists(p.first) )
		{
			table[p.first].setValue( p.second );
		}
		else
		{
			assert("!Update clocks try to update a clock that doesn't exists");
		}
	}
	messages.clear();
}

bool ClockTable::exists(const std::string name) const
{
	auto it = table.find(name);
	return it != table.end();
}