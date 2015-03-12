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

int SymbolTable::getEntry(std::string name)
{
	return table[name];
}
