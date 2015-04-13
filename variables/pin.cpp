#include "pin.h"

#include <cassert>

Pin::Pin()
{

}

Pin::Pin(std::string n, std::string s, int p) : name(n),  status(s), port(p)
{
	assert(p > -1);
}

Pin::Pin( const Pin& rhs ) : name(rhs.name), status(rhs.status), port(rhs.port)
{

}

Pin::Pin( const Pin&& rhs ) : name(std::move(rhs.name)), status(std::move(rhs.status)), port(std::move(rhs.port))
{

}

Pin& Pin::operator=(const Pin& rhs)
{
	name = rhs.name;
	status = rhs.status;
	port = rhs.port;
	return *this;
}

std::string Pin::getName() const
{
	return name;
}

int Pin::getValue() const
{
	return value;
}

void Pin::update()
{
	/* here reads data from the pin */
	if ( status == "IN" )
	{
		static int i = 0;
		value = ++i;
	}
}

void Pin::setValue(int value)
{
	/* here writes data on the pin */
	if ( status == "OUT" )
	{
		this->value = value;
	}
}