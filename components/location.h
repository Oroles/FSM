#ifndef _STATE_H_
#define _STATE_H_

#include <string>
#include <iostream>
#include <cassert>

class Location
{
public:
	Location();
	Location(const std::string n, const std::string type);
	Location(const Location& rhs);
	Location(Location&& rhs);

	const Location& operator=(const Location& rhs);
	bool operator==(const Location& rhs) const;
	bool operator!=(const Location& rhs) const;

	friend std::ostream& operator<<(std::ostream& o, const Location& rhs);

	std::string getName() const;
	std::string getType() const;
	void setName(std::string n);

private:
	std::string name;
	std::string type;
};

#endif