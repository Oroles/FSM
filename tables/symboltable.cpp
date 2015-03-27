#include "symboltable.h"

#include <cassert>

SymbolTable& SymbolTable::getInstance()
{
	static SymbolTable instance;
	return instance;
}

SymbolTable::SymbolTable()
{
	
}

void SymbolTable::setValue(std::string name, int value)
{
	if ( this->exists(name) )
	{
		table[name] = value;
	}
	else
	{
		assert(!"Symbol table set value to an unexisting symbol");
	}
}

int SymbolTable::getValue(const std::string name)
{
	if ( this->exists(name) )
	{
		return table[name];
	}
	else
	{
		assert("Symbol table get value to an unexisting symbol");
	}
	return -1;
}

bool SymbolTable::exists(const std::string name) const
{
	auto it = table.find(name);
	return it != table.end();
}

void SymbolTable::addEntries(const std::vector<std::pair<std::string,int>> entries)
{
	for ( auto it :entries )
	{
		if ( !this->exists(it.first) )
		{
			table[it.first] = it.second;
		}
		else
		{
			assert(!"Symbol table value already exits in table");
		}
	}
}
