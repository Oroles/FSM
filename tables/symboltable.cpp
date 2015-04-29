#include "symboltable.h"
#include "pintable.h"

#include "../utils/utils.h"

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
		if ( is_array(name) )
		{
			messages.push_back( PlainData{nameOfTheArray(name),positionOfTheArray(name),value} );
		}
		else
		{
			messages.push_back( PlainData{name,0,value} );
		}
	}
	else
	{
		assert(!"Symbol table set value to an unexisting symbol");
	}
}

void SymbolTable::updateSymbols()
{
	for ( auto& p : messages )
	{
		table[p.name][p.size] = p.defaultValue;
	}
	messages.clear();
}

int SymbolTable::getValue(const std::string name)
{

	if ( this->exists(name) )
	{
		if ( is_array(name) )
		{
			int aux = table[nameOfTheArray(name)][positionOfTheArray(name)];
			return aux;
		}
		else
		{
			return table[name][0];
		}
	}
	else
	{
		assert("Symbol table get value to an unexisting symbol");
	}
	return -1;
}

bool SymbolTable::exists(const std::string name) const
{
	std::string variableName = nameOfTheArray(name);
	auto it = table.find(variableName);
	return it != table.end();
}

void SymbolTable::addEntries(const std::vector<PlainData> entries)
{
	for ( auto it :entries )
	{
		if ( !this->exists(it.name) )
		{
			if ( !PinTable::getInstance().exists(it.name) )
			{
				table[it.name] = std::unique_ptr<int[]>( new int[it.size] );
				if ( it.size == 1 )
				{
					table[it.name][0] = it.defaultValue; 
				}
			}
		}
		else
		{
			assert(!"Symbol table value already exits in table");
		}
	}
}
