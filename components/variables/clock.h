#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <string>
#include <iostream>
#include <cassert>

class Clock
{
public:
	Clock( std::string n, int val );
	Clock(const Clock& rhs);
	Clock& operator=(const Clock& rhs);
	bool operator==(const Clock& rhs);
	friend std::ostream& operator<<(std::ostream& o, const Clock& c );

	void setValue(int value);
	int getValue() const;
	std::string getName() const;
	void update();

	~Clock();
private:
	std::string name;
	int value = 0;
};

#endif