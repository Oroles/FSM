#include "chanbroadcast.h"

#include <iostream>
#include <cassert>

ChanBroadcast::ChanBroadcast(const std::string n) : Chan(n)
{
	assert(n.size() != 0);
}

ChanBroadcast::ChanBroadcast(const ChanBroadcast& c) : Chan(c.name)
{
	assert(name.size() != 0);
}

ChanBroadcast::ChanBroadcast(ChanBroadcast&& c) : Chan(std::move(c.name))
{

}

const ChanBroadcast& ChanBroadcast::operator=(const ChanBroadcast& c)
{
	Chan::operator=(c);
	return *this;
}

bool ChanBroadcast::operator==(const ChanBroadcast& c)
{
	return name == c.getName();
}

std::ostream& operator<<(std::ostream& o, const ChanBroadcast& c)
{
	std::cout << "ChanBroadcast " << c.getName();
	return o;
}

Chan::ChanType ChanBroadcast::getType() const
{
	return Chan::ChanType::Broadcast;
}

ChanBroadcast::~ChanBroadcast()
{

}