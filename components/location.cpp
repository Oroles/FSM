#include "location.h"

Location::Location() : name("")
{

}

Location::Location(const std::string n, const std::string t) : name(n), type(t)
{
}

Location::Location(const Location& rhs) : name(rhs.name), type(rhs.type), expressions(rhs.expressions)
{
	assert(rhs.getName().size() != 0);
}

Location::Location(Location&& rhs) : name(std::move(rhs.name)), type(std::move(rhs.type)), expressions(std::move(rhs.expressions))
{

}

const Location& Location::operator=(const Location& rhs)
{
	name = rhs.name;
	type = rhs.type;
	expressions = rhs.expressions;
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

std::string Location::getType() const
{
	return type;
}

void Location::setName(std::string n)
{
	assert(n != "" );
	name = n;
}

void Location::setType(std::string t)
{
	assert(t != "" );
	type = t;
}

void Location::addExpression(const Expression& e)
{
	expressions.push_back(e);
}

bool Location::isAvailable() const
{
	for ( auto& ex : expressions )
	{
		if ( ex.evaluate() == false )
		{
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& o, const Location& rhs)
{
	o << "Location: " << rhs.name;
	return o;
}