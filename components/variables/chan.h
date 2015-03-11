#ifndef _CHAN_H_
#define _CHAN_H_

#include <string>
#include <cassert>

class Chan
{
public:
	Chan( std::string n, int val = 0 ) : name(n), value(val)
	{
		assert(n.size() != 0);
	}
	Chan(const Chan& rhs);
	Chan& operator=(const Chan& rhs);
	bool operator==(const Chan& rhs);

	void set(int value);
	int get();

	~Chan();

private:
	std::string name;
	int value = 0;
};

#endif