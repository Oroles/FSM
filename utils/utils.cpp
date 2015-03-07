#include "utils.h"
#include <algorithm>
#include <cassert>

DebugMessagePriority priority;

void setPriority(const std::vector<std::string>& args)
{
	auto it = std::find(args.begin(), args.end(), "-d" );
	if ( it == args.end() )
	{
		priority.setPriority(DebugMessagePriority::Priority::NoMessage);
	}
	else
	{
		if ( ++it == args.end() )
		{
			assert(true); //It should not reach this state;
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