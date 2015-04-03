#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <vector>
#include <algorithm>

#include "debugmessagepriority.h"

extern DebugMessagePriority priority;
extern bool quitApp;

void setPriority(const std::vector<std::string>& args);
std::string getFileName(const std::vector<std::string>& args);
bool setStepProgress(const std::vector<std::string>& args);
void nextStep();

bool is_integer(std::string name); //Checks if the string contains only numbers
std::vector<std::string> splitString(std::string data, const std::string split);

template< class T >
void displayMessage(const DebugMessagePriority& p, const T& msg)
{
	if ( ( priority & p ) != 0 )
	{
		std::cout << msg << std::endl;
	}
}

template< class T >
void displayMessage(const DebugMessagePriority& p, const T&& msg)
{
	if ( ( priority & p ) != 0 )
	{
		std::cout << msg << std::endl;
	}
}

template < class T >
void display(const DebugMessagePriority& p, T msg)
{
	if ( ( priority & p ) != 0 )
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