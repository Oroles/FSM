#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "../utils/plaindata.h"
#include "../utils/utils.h"

class SymbolTable
{
public:
	static SymbolTable& getInstance();
	void addEntries(const std::vector<PlainData> );
	void setValue(const std::string name, const int value);
	int getValue(const std::string name);
	bool exists(const std::string name) const;
	void updateSymbols();

private:
	SymbolTable();
	SymbolTable(const SymbolTable& rhs) = delete;
	SymbolTable& operator=(const SymbolTable& rhs) = delete;

	std::map< std::string,std::unique_ptr<int[]> > table;
	std::vector<PlainData> messages;
};

#endif