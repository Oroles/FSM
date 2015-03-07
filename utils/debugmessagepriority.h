#ifndef _DEBUG_MESSAGE_PRIORITY_H_
#define _DEBUG_MESSAGE_PRIORITY_H_

#include <iostream>
/*
How to use:
	see file components/module.cpp for a call
	A higher value for priority equals a higher priority for the message
	All the message under or equal to currentPriority will be display
*/

class DebugMessagePriority
{
public:
	enum class Priority : int { AllMessages = -1, Level0 = 0, Level1 = 1, Level2 = 2, Level3 = 3, NoMessage = 4 };

	DebugMessagePriority() : priority{Priority::NoMessage} {}
	DebugMessagePriority(Priority p) 
	{
		priority = p;
	}

	bool operator==(const DebugMessagePriority& rhs)
	{
		return priority == rhs.getPriority();
	}
	bool operator>(const DebugMessagePriority& rhs)
	{
		return priority > rhs.getPriority();
	}
	bool operator<(const DebugMessagePriority& rhs)
	{
		return priority < rhs.getPriority();
	}
	bool operator<=(const DebugMessagePriority& rhs)
	{
		return priority <= rhs.getPriority();
	}

	void setPriority(Priority p)
	{
		priority = p;
	}

	Priority getPriority() const
	{
		return priority;
	}

private:
	Priority priority;
};

#endif