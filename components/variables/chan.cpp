#include "chan.h"

Chan::Chan(const Chan& rhs) : Variable(rhs), value(rhs.value)
{

}

Chan::~Chan()
{
	
}

Chan& Chan::operator=(const Chan& rhs)
{
	Variable::operator=(rhs);
	value=rhs.value;
	return *this;
}

bool Chan::operator==(const Chan& rhs)
{
	bool rez = Variable::operator==(rhs);
	return rez;
}


void Chan::set( int val )
{
	value = val;
}

int Chan::get()
{
	return value;
}