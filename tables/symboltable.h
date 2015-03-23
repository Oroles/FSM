#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <map>
#include <string>

class SymbolTable
{
public:
	static SymbolTable& getInstance();
	void setValue(std::string name, int value);
	int getValue(const std::string name);
	bool exists(const std::string name) const;
private:
	SymbolTable();
	SymbolTable(const SymbolTable& rhs) = delete;
	SymbolTable& operator=(const SymbolTable& rhs) = delete;

	std::map<std::string,int> table;
};

#endif