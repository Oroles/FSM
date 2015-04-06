#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <map>
#include <string>
#include <vector>

class SymbolTable
{
public:
	static SymbolTable& getInstance();
	void addEntries(const std::vector<std::pair<std::string,int> > );
	void setValue(const std::string name, const int value);
	int getValue(const std::string name);
	bool exists(const std::string name) const;
	void updateSymbols();

private:
	SymbolTable();
	SymbolTable(const SymbolTable& rhs) = delete;
	SymbolTable& operator=(const SymbolTable& rhs) = delete;

	std::map<std::string,int> table;
	std::vector<std::pair<std::string,int> > messages;
};

#endif