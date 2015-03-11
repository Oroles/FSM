#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <string>
#include <cassert>

class Clock
{
public:
	Clock( std::string n, int val = 0) : name(n), value(val)
	{
		assert(n.size() != 0 );
		assert(val >= 0 );
	}

	Clock(const Clock& rhs);
	Clock& operator=(const Clock& rhs);
	bool operator==(const Clock& rhs);

	void set(int value);
	int get() const;
	void update();

	~Clock();
private:
	std::string name;
	int value = 0;
};

#endif