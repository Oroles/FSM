#include "chanurgent.h"
#include <iostream>
#include <cassert>

ChanUrgent::ChanUrgent(std::string n) : Chan(n)
{
	assert(n != "");
}

ChanUrgent::ChanUrgent(const ChanUrgent& rhs) : Chan(rhs.name)
{
	assert(rhs.name != "");
}

ChanUrgent::ChanUrgent(ChanUrgent&& rhs) : Chan(std::move(rhs.name))
{

}
const ChanUrgent& ChanUrgent::operator=(const ChanUrgent& rhs)
{
	Chan::operator=(rhs);
	return *this;
}

bool ChanUrgent::operator==(const ChanUrgent& rhs)
{
	return name == rhs.name;
}

std::ostream& operator<<(std::ostream& o, const ChanUrgent& rhs)
{
	std::cout << "Urgent chan" << rhs.getName();
	return o;
}

Chan::ChanType ChanUrgent::getType() const
{
	return Chan::ChanType::Urgent;
}

ChanUrgent::~ChanUrgent()
{

}