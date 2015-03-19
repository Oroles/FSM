#include "symboltable.h"

SymbolTable& SymbolTable::getInstance()
{
	static SymbolTable instance;
	return instance;
}

SymbolTable::SymbolTable()
{
	
}

void SymbolTable::updateEntry(std::string name, int value)
{
	table[name] = value;
}

int SymbolTable::getEntry(const std::string name)
{
	return table[name];
}

bool SymbolTable::exists(const std::string name) const
{
	auto it = table.find(name);
	return it != table.end();
}
