#include "clock.h"

Clock::Clock( std::string n, int val ) : name(n), value(val)
{
	assert(n.size() != 0 );
	assert(val >= 0 );

	size_t pos_space = name.find(" ");
	name = name.substr(pos_space+1,std::string::npos);
	name = name.substr(0,name.find(";"));
}

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

void Clock::setValue(int val)
{
	value = val;
}

int Clock::getValue() const
{
	return value;
}

std::string Clock::getName() const
{
	return name;
}

void Clock::update()
{
	++value;
}

std::ostream& operator<<(std::ostream& o, const Clock& c)
{
	o << "Clock: " << c.getName() << " with value " << c.getValue();
	return o;
}