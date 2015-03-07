#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <vector>
#include <algorithm>

#include "debugmessagepriority.h"

extern DebugMessagePriority priority;
void setPriority(const std::vector<std::string>& args);

template< class T >
void displayMessage(const DebugMessagePriority& p, const T& msg)
{
	if ( priority <= p )
	{
		std::cout << msg << std::endl;
	}
}

template< class T >
void displayMessage(const DebugMessagePriority& p, const T&& msg)
{
	if ( priority <= p )
	{
		std::cout << msg << std::endl;
	}
}

template < class T >
void display(const DebugMessagePriority& p, T msg)
{
	if ( priority <= p )
	{
		std::cout << msg << " ";
	}
}

template < class T, class... Args >
void display(const DebugMessagePriority& p, T t, Args... args)
{
	display(p,t);
	display(p,args...);
}

#endif