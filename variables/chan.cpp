#include "chan.h"

Chan::Chan(std::string n) : name(n)
{

}

Chan::Chan(const Chan& c) : name( c.name )
{

}

Chan::Chan(Chan&& c) : name( std::move( c.name ) )
{

}

const Chan& Chan::operator=(const Chan& c)
{
	name = c.name;
	return *this;
}

bool Chan::operator==(const Chan& c)
{
	return name == c.name;
}

std::ostream& operator<<(std::ostream& o, const Chan& c)
{
	o << "Chan " << c.getName();
	return o;
}

Chan::~Chan()
{

}

std::string Chan::getName() const
{
	return name;
}
