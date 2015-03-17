#ifndef _CHAN_H_
#define _CHAN_H_

#include <string>
#include <iostream>
#include <cassert>

class Chan
{
public:
	Chan( std::string n, int val );
	Chan(const Chan& rhs);
	Chan(Chan&& rhs);
	Chan& operator=(const Chan& rhs);
	bool operator==(const Chan& rhs);
	friend std::ostream& operator<<(std::ostream& o, const Chan& c);

	void setValue(int value);
	int getValue() const;
	std::string getName() const;

	~Chan();

private:
	std::string name;
	int value = 0;
};

#endif