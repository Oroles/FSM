#ifndef _CLOCK_TABLE_H_
#define _CLOCK_TABLE_H_

#include <map>
#include <vector>
#include <string>

#include "../variables/clock.h"

class ClockTable
{
public:
	static ClockTable& getInstance();
	void addEntry(const Clock& c);
	void addEntries(const std::vector<Clock>& v);
	int getValue(const std::string name);
	void setValue(const std::string name, int value);
	void updateClocks();
	bool exists(const std::string name) const;

private:
	ClockTable();
	ClockTable(const ClockTable& rhs) = delete;
	ClockTable(ClockTable&& rhs) = delete;
	ClockTable& operator=(const ClockTable& rhs);

	std::map<std::string,Clock> table;
	std::vector<std::pair<std::string,int>> messages;
};

#endif