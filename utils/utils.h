#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>

static bool allowDebug = false;

template< class T >
void displayMessage(const T& msg)
{
	if (allowDebug == true )
	{
		std::cout << msg << std::endl;
	}
}

template< class T >
void displayMessage(const T&& msg)
{
	if (allowDebug == true )
	{
		std::cout << msg << std::endl;
	}
}

template < class T >
void display(T msg)
{
	if ( allowDebug == true )
	{
		std::cout << msg << " ";
	}
}

template < class T, class... Args >
void display(T t, Args... args)
{
	display(t);
	display(args...);
}

#endif