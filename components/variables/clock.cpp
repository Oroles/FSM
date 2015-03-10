#include "clock.h"


Clock::Clock(const Clock& rhs) : Variable(rhs), value(rhs.value)
{
	assert(rhs.value >= 0);
}

Clock::~Clock()
{
	
}

Clock& Clock::operator=(const Clock& rhs)
{
	Variable::operator=(rhs);
	value = rhs.value;
	return *this;
}

bool Clock::operator==(const Clock& rhs)
{
	bool rez = Variable::operator==(rhs);
	return rez;
}

void Clock::set(int val)
{
	value = val;
}

int Clock::get()
{
	return value;
}