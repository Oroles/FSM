#include "localtable.h"

#include <cassert>
#include "../utils/utils.h"

LocalTable& LocalTable::getInstance()
{
	static LocalTable instance;
	return instance;
}

LocalTable::LocalTable()
{

}

LocalTable::~LocalTable()
{
	for ( auto& it : container )
	{
		for ( auto& j : it.second )
		{
			delete[] j.second.second;
		}
	}
	for ( auto& it : templates )
	{
		for ( auto& j : it.second )
		{
			delete[] j.second.second;
		}
	}
}

void LocalTable::setValue(const std::string table, const std::string variable,  int value)
{
	if ( this->exists(table,variable) )
	{
		if ( is_array(variable) )
		{
			container[table][nameOfTheArray(variable)].second[positionOfTheArray(variable)] = value;
		}
		else
		{
			container[table][variable].second[0] = value;
		}
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
		if ( is_array(variable))
		{
			auto t = container[table];
			return t[nameOfTheArray(variable)].second[positionOfTheArray(variable)];
		}
		else
		{
			auto t = container[table];
			return t[variable].second[0];
		}
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
		std::string variableName = nameOfTheArray(variable);
		auto i = t.find(variableName);
		return i != t.end();
	}
	return false;
}

void LocalTable::addEntries(const std::string table, const std::vector<PlainData> entries)
{
	for ( auto it :entries )
	{
		if ( !this->exists(table,it.name) )
		{
			templates[table][it.name].second = new int[it.size];
			templates[table][it.name].first = it.size;
			if ( it.size == 1 )
			{
				templates[table][it.name].second[0] = it.defaultValue;
			}
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
	/* Here we set the container to point to another memory 
	In this case we didn't affect the template memory */
	for ( auto& t : container[newName] )
	{
		t.second.second = new int[ t.second.first ];
		*(t.second.second) = *(templates[currentName][t.first].second);
	}
}

std::vector<std::string> LocalTable::getValue(const std::string variable)
{
	std::vector< std::string > rez;
	for ( auto& i : container )
	{
		std::map<std::string,std::pair<int,int*>> table = i.second;
		for ( auto& t : table )
		{
			if ( t.first == variable )
			{
				rez.push_back( std::string( "In template " + i.first + " variable " + t.first + " = " + std::to_string(t.second.second[0]) ) );
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