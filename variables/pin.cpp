#include "pin.h"
#include "../utils/utils.h"

#include <cassert>
#include <wiringPi.h>

Pin::Pin()
{

}

Pin::Pin(std::string n, std::string s, int p) : name(n),  status(s), port(p)
{
	assert(p > -1);
#ifdef RASPBERRY_PI
	if (status == "OUT" )
	{
		pinMode(port,OUTPUT);
	}
	else
	{
		pinMode(port,INPUT);
	}
#else
	display(DebugMessagePriority::Pin, "The pin: ", port, "is set as ", status, "\n" );
#endif
}

Pin::Pin( const Pin& rhs ) : name(rhs.name), status(rhs.status), port(rhs.port)
{
#ifdef RASPBERRY_PI
	if (status == "OUT" )
	{
		pinMode(port,OUTPUT);
	}
	else
	{
		pinMode(port,INPUT);
	}
#else
	display(DebugMessagePriority::Pin, "The pin: ", port, "is set as ", status, "\n" );
#endif
}

Pin::Pin( const Pin&& rhs ) : name(std::move(rhs.name)), status(std::move(rhs.status)), port(std::move(rhs.port))
{
#ifdef RASPBERRY_PI
	if (status == "OUT" )
	{
		pinMode(port,OUTPUT);
	}
	else
	{
		pinMode(port,INPUT);
	}
#else
	display(DebugMessagePriority::Pin, "The pin: ", port, "is set as ", status, "\n" );
#endif
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
#ifdef RASPBERRY_PI
		value = digitalRead(port);
#else
		static int i = 0;
		value = ++i;
#endif
	}
}

void Pin::setValue(int value)
{
	/* here writes data on the pin */
	if ( status == "OUT" )
	{
#ifdef RASPBERRY_PI
		digitalWrite(port,value);
#else
		this->value = value;
#endif
	}
}