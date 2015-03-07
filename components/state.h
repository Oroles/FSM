#ifndef _STATE_H_
#define _STATE_H_

#include <string>
#include <iostream>
#include <cassert>

class State
{
public:
	State() : name("")
	{

	}

	State(const std::string n) : name(n) 
	{
		assert(n.size() != 0 );
	}

	State(const State& rhs) : name(rhs.name)
	{
		assert(rhs.getName().size() != 0);
	}

	State& operator=(const State& rhs)
	{
		name = rhs.name;
		return *this;
	}

	friend bool operator==(const State& lhs, const State& rhs)
	{
		return lhs.getName() == rhs.getName();
	}
	friend std::ostream& operator<<(std::ostream& o, const State& rhs)
	{
		o << "State: " << rhs.name;
		return o;
	}

	std::string getName() const
	{
		return name;
	}

	void setName(std::string n)
	{
		assert(n.size() != 0 );
		name = n;
	}

private:
	std::string name;
};

#endif