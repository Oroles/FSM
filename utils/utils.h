#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <vector>
#include <algorithm>

#include "debugmessagepriority.h"

extern DebugMessagePriority priority;
extern bool quitApp;

enum class TranzactionAvailableStatus : int { Available, NotGuard, NotSource };

void setPriority(const std::vector<std::string>& args);
std::string getFileName(const std::vector<std::string>& args);
bool setStepProgress(const std::vector<std::string>& args);
bool setQuit(const std::vector<std::string>& args);
void nextStep();

bool is_integer(const std::string name); //Checks if the string contains only numbers
bool is_array(const std::string name); //Checkss if the name contains "["
std::string nameOfTheArray(const std::string name); //gets the name of the array eg a[5] -> a
int positionOfTheArray(const std::string name); //gets the index of the array eg a[5] -> 5
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