#include "chanbroadcast.h"

ChanBroadcast::ChanBroadcast(const std::string n) : Chan(n)
{

}

ChanBroadcast::ChanBroadcast(const ChanBroadcast& c) : Chan(c.name)
{

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

bool ChanBroadcast::isSenderSync()
{
	return true;
}

bool ChanBroadcast::isReceiverSync()
{
	return true;
}

Chan::ChanType ChanBroadcast::getType() const
{
	return Chan::ChanType::Broadcast;
}

ChanBroadcast::~ChanBroadcast()
{

}