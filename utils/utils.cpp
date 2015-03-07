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
		priority.setPriority(DebugMessagePriority::Priority::NoMessage);
	}
	else
	{
		if ( ++it == args.end() )
		{
			assert(!"Add a display level after -d"); //It should not reach this state;
			priority.setPriority(DebugMessagePriority::Priority::NoMessage);
		}
		else
		{
			int val = std::stoi(*it);
			switch( val )
			{
				case -1: priority.setPriority(DebugMessagePriority::Priority::AllMessages); break;
				case 0: priority.setPriority(DebugMessagePriority::Priority::Level0); break;
				case 1: priority.setPriority(DebugMessagePriority::Priority::Level1); break;
				case 2: priority.setPriority(DebugMessagePriority::Priority::Level2); break;
				case 3: priority.setPriority(DebugMessagePriority::Priority::Level3); break;
				case 4: priority.setPriority(DebugMessagePriority::Priority::NoMessage); break;
			}
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