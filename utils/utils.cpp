#include "utils.h"
#include <algorithm>
#include <cassert>

DebugMessagePriority priority;
bool stepProgress = false;

void setPriority(const std::vector<std::string>& args)
{
	auto it = std::find(args.begin(), args.end(), "-d");
	if ( it == args.end() )
	{
		priority.setPriority(0);
	}
	else
	{
		if ( ++it == args.end() )
		{
			assert(!"Add a display level after -d"); //It should not reach this state;
			priority.setPriority(0);
		}
		else
		{
			int val = std::stoi(*it);
			priority.setPriority(val);
		}
	}
}

std::string getFileName(const std::vector<std::string>& args)
{
	auto it = std::find(args.begin(), args.end(), "-i");
	if ( it == args.end() )
	{
		assert(!"Insert -i to add the filename"); //It should not reach this state;
		return "";
	}
	else
	{
		if ( ++it == args.end() )
		{
			assert(!"Add a filename after -i"); //It should not reach this state;
			return "";
		}
		else
		{
			return *it;
		}
	}
}

bool setStepProgress(const std::vector<std::string>& args)
{
	auto it = std::find(args.begin(), args.end(), "-step");
	if ( it == args.end() )
	{
		stepProgress = false;
		return false;
	}
	else
	{
		stepProgress = true;
		return true;
	}
}

void nextStep()
{
	if ( stepProgress == true )
	{
		std::string aux;
		while( aux != "s")
		{
			std::cout << "Press s to make progress: ";
			std::cin >> aux;
		}
	}
	return;
}

bool is_integer(std::string name)
{
	size_t pos = name.find_first_not_of("0123456789");
	return pos == std::string::npos;
}

std::vector<std::string> splitString(std::string data, const std::string split)
{
	std::vector<std::string> rez;
	data.erase(std::remove_if(data.begin(),data.end(),isspace), data.end());
	size_t poz;
	while( ( poz = data.find(split) ) != std::string::npos )
	{
		std::string aux = data.substr(0,poz);
		rez.push_back( aux );
		data = data.substr(poz+split.length(),std::string::npos);
	}
	rez.push_back( data );
	return rez;
}