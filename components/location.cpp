#include "location.h"

Location::Location() : name("")
{

}

Location::Location(const std::string n) : name(n) 
{
	//assert(n.size() != 0 );
}

Location::Location(const Location& rhs) : name(rhs.name)
{
	assert(rhs.getName().size() != 0);
}

Location::Location(Location&& rhs) : name(std::move(rhs.name))
{

}

const Location& Location::operator=(const Location& rhs)
{
	name = rhs.name;
	return *this;
}

bool Location::operator==(const Location& rhs) const
{
	return name == rhs.getName();
}

bool Location::operator!=(const Location& rhs) const
{
	return name != rhs.getName();
}

std::string Location::getName() const
{
	return name;
}

void Location::setName(std::string n)
{
	assert(n.size() != 0 );
	name = n;
}

std::ostream& operator<<(std::ostream& o, const Location& rhs)
{
	o << "Location: " << rhs.name;
	return o;
}