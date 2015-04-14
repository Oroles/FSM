#include "pintable.h"

#include <cassert>
#include <iostream>

PinTable& PinTable::getInstance()
{
	static PinTable instance;
	return instance;
}

PinTable::PinTable()
{
}

bool PinTable::exists(std::string name)
{
	return table.find( name ) != table.end();
}

void PinTable::addEntry(const std::string name, const std::string status, const int port)
{
	if ( this->exists(name) )
	{
		assert(!"Pin already exists in PinTable");
	}
	table[name] = Pin(name,status,port);
}

void PinTable::addEntries(const std::vector<Pin> pins)
{
	for ( auto& p : pins )
	{
		if ( table.find( p.getName() ) != table.end() )
		{
			assert(!"Pin already exists in Pintable" );
		}
		table[p.getName()] = p;
	}
}

/* This method reads the data from the pin and store it in the register */
void PinTable::updateEntry(const std::string name)
{
	if ( !this->exists(name) )
	{
		assert(!"Pin update doesn't exists in PinTable");
	}
	table[name].update();
}

/* This method reads the data from the register and return it */
int PinTable::getValue(const std::string name)
{
	if ( !this->exists(name) )
	{
		assert(!"Pin get value doesn't exists in PinTable");
	}
	return table[name].getValue();
}

/* This method writes the data directly on the pin */
void PinTable::setValue(const std::string name, int value)
{
	if ( !this->exists(name) )
	{
		assert(!"Pin set value doesn't exists in PinTable");
	}
	messages.push_back( std::pair<std::string,int>( name, value ) );
}

void PinTable::updatePins()
{
	for ( auto& p : messages )
	{
		table[p.first].setValue(p.second);
	}
	messages.clear();
}