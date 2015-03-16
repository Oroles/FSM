#include "chan.h"

Chan::Chan( std::string n, int val ) : name(n), value(val)
{
	assert(n.size() != 0);

	size_t pos_space = name.find(" ");
	name = name.substr(pos_space+1,std::string::npos);
	name = name.substr(0,name.find(";"));
}

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


void Chan::setValue( int val )
{
	value = val;
}

int Chan::getValue() const
{
	return value;
}

std::string Chan::getName() const
{
	return name;
}

std::ostream& operator<<(std::ostream& o, const Chan& c)
{
	o << "Chan " << c.getName() << " with value " << c.getValue() ;
	return o;
}