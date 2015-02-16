#include "pin.h"
#include "../utils/utils.h"

#include <cassert>
#include <wiringPi.h>

Pin::Pin()
{

}

Pin::Pin(std::string n, std::string s, int p) : name(n),  status(s), port(p), value(0)
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
#endif
	display(DebugMessagePriority::Pin, "The ", name, "on pin: ", port, "is set as ", status, "\n" );
}

Pin::Pin( const Pin& rhs ) : name(rhs.name), status(rhs.status), port(rhs.port), value(rhs.value)
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
#endif
	display(DebugMessagePriority::Pin, "The ", name, "on pin: ", port, "is set as ", status, "\n" );
}

Pin::Pin( const Pin&& rhs ) : name(std::move(rhs.name)), status(std::move(rhs.status)), port(std::move(rhs.port)), value(std::move(rhs.value))
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
#endif
	display(DebugMessagePriority::Pin, "The ", name, "on pin: ", port, "is set as ", status, "\n" );
}

Pin& Pin::operator=(const Pin& rhs)
{
	name = rhs.name;
	status = rhs.status;
	port = rhs.port;
	value = rhs.value;
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
		static int i = 1;
		value = i;
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

#endif
	}
}
