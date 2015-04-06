#ifndef _PIN_TABLE_H_
#define _PIN_TABLE_H_

#include "../variables/pin.h"

#include <map>
#include <vector>
#include <string>

class PinTable
{
public:
	static PinTable& getInstance();
	bool exists( std::string name );
	void addEntry( const std::string name,const std::string status, const int port );
	void addEntries( const std::vector<Pin> );
	void updateEntry( const std::string name );
	void updatePins();
	int getValue( const std::string name );
	void setValue( const std::string name, int value );

private:
	PinTable();
	PinTable(const PinTable& rhs) = delete;
	PinTable(const PinTable&& rhs) = delete;
	PinTable& operator=(const PinTable& rhs) = delete;

	std::map<std::string,Pin> table;
	std::vector<std::pair<std::string,int> > messages;
};

#endif