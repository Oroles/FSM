#include "chan.h"

Chan::Chan(const Chan& rhs) : name(rhs.name), value(rhs.value)
{
	assert(name.size() != 0);
}

Chan::~Chan()
{
	
}

Chan& Chan::operator=(const Chan& rhs)
{
	name=rhs.name;
	value=rhs.value;
	return *this;
}

bool Chan::operator==(const Chan& rhs)
{
	return name == rhs.name;
}


void Chan::set( int val )
{
	value = val;
}

int Chan::get()
{
	return value;
}