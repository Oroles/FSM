#ifndef _LOCAL_TABLE_H_
#define _LOCAL_TABLE_H_

#include <map>
#include <string>
#include <vector>
#include <iostream>

class LocalTable
{
public:
	static LocalTable& getInstance();
	void addEntries(const std::string table, const std::vector<std::pair<std::string,int> > );
	void setValue(const std::string table, const std::string variable, const int value);
	int getValue(const std::string table, const std::string variable);
	bool exists(const std::string table, const std::string variable);
	void generateTables(const std::string currentName, const std::string newName );

private:
	LocalTable();
	LocalTable(const LocalTable& ) = delete;
	LocalTable(const LocalTable&& ) = delete;
	LocalTable& operator=(const LocalTable& ) = delete;

	typedef std::map<std::string,int> table;
	std::map<std::string,table> container;
	std::map<std::string,table> templates;
};

#endif