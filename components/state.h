#ifndef _STATE_H_
#define _STATE_H_

#include <string>

class State
{
public:
	State() : name("")
	{

	}

	State(const std::string n) : name(n) 
	{

	}

	State(const State& rhs) : name(rhs.name)
	{

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

	std::string getName() const
	{
		return name;
	}

	void setName(std::string n)
	{
		name = n;
	}

private:
	std::string name;
};

#endif