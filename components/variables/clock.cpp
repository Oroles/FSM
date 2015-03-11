#include "clock.h"

Clock::Clock(const Clock& rhs) : name(rhs.name), value(rhs.value)
{
	assert(rhs.name.size() != 0);
	assert(rhs.value >= 0);
}

Clock::~Clock()
{
	
}

Clock& Clock::operator=(const Clock& rhs)
{
	name = rhs.name;
	value = rhs.value;
	return *this;
}

bool Clock::operator==(const Clock& rhs)
{
	return name == rhs.name;
}

void Clock::set(int val)
{
	value = val;
}

int Clock::get() const
{
	return value;
}

void Clock::update()
{
	++value;
}