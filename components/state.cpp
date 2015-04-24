#include "state.h"

State::State() : name("")
{

}

State::State(const std::string n) : name(n) 
{
	//assert(n.size() != 0 );
}

State::State(const State& rhs) : name(rhs.name)
{
	assert(rhs.getName().size() != 0);
}

State::State(State&& rhs) : name(std::move(rhs.name))
{

}

State& State::operator=(const State& rhs)
{
	name = rhs.name;
	return *this;
}

bool State::operator==(const State& rhs) const
{
	return name == rhs.getName();
}

bool State::operator!=(const State& rhs) const
{
	return name != rhs.getName();
}

std::string State::getName() const
{
	return name;
}

void State::setName(std::string n)
{
	assert(n.size() != 0 );
	name = n;
}

std::ostream& operator<<(std::ostream& o, const State& rhs)
{
	o << "State: " << rhs.name;
	return o;
}