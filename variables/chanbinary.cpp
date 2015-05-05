#include "chanbinary.h"

#include <iostream>
#include <cassert>

ChanBinary::ChanBinary( std::string n) : Chan(n)
{
	assert(n.size() != 0);
}

ChanBinary::ChanBinary(const ChanBinary& rhs) : Chan(rhs.name)
{
	assert(name.size() != 0);
}

ChanBinary::ChanBinary(ChanBinary&& rhs) : Chan(std::move(rhs.name))
{
	
}

ChanBinary::~ChanBinary()
{
	
}

Chan::ChanType ChanBinary::getType() const
{
	return Chan::ChanType::Binary;
}

const ChanBinary& ChanBinary::operator=(const ChanBinary& rhs)
{
	Chan::operator=(rhs);
	return *this;
}

bool ChanBinary::operator==(const ChanBinary& rhs)
{
	return name == rhs.name;
}

std::ostream& operator<<(std::ostream& o, const ChanBinary& c)
{
	o << "ChanBinary " << c.getName();
	return o;
}