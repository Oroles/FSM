#include "localtable.h"

#include <cassert>

LocalTable& LocalTable::getInstance()
{
	static LocalTable instance;
	return instance;
}

LocalTable::LocalTable()
{

}

void LocalTable::setValue(const std::string table, const std::string variable,  int value)
{
	if ( this->exists(table,variable) )
	{
		container[table][variable] = value;
	}
	else
	{
		assert(!"Symbol table set value to an unexisting symbol");
	}
}

int LocalTable::getValue(const std::string table, const std::string variable)
{
	if ( this->exists(table,variable) )
	{
		auto t = container[table];
		return t[variable];
	}
	else
	{
		assert("Symbol table get value to an unexisting symbol");
	}
	return -1;
}

bool LocalTable::exists(const std::string table, const std::string variable)
{
	auto it = container.find(table);
	if ( it != container.end() )
	{
		auto t = container[table];
		auto i = t.find(variable);
		return i != t.end();
	}
	return false;
}

void LocalTable::addEntries(const std::string table, const std::vector<std::pair<std::string,int>> entries)
{
	for ( auto it :entries )
	{
		if ( !this->exists(table,it.first) )
		{
			templates[table][it.first] = it.second;
		}
		else
		{
			assert(!"Symbol table value already exits in table");
		}
	}
}

void LocalTable::generateTables(const std::string currentName, const std::string newName )
{
	container[newName] = templates[currentName];
}

std::vector<std::string> LocalTable::getValue(const std::string variable)
{
	std::vector< std::string > rez;
	for ( auto& i : container )
	{
		std::map<std::string,int> table = i.second;
		for ( auto& t : table )
		{
			if ( t.first == variable )
			{
				rez.push_back( std::string( "In template " + i.first + " variable " + t.first + " = " + std::to_string(t.second) ) );
			}
		}
	}
	return rez;
}

bool LocalTable::exists(const std::string variable )
{
	for ( auto& i : container )
	{
		auto table = i.second;
		for(  auto& t : table )
		{
			if ( t.first == variable )
			{
				return true;
			}
		}
	}
	return false;
}