#ifndef _DEBUG_MESSAGE_PRIORITY_H_
#define _DEBUG_MESSAGE_PRIORITY_H_

#include <iostream>

class DebugMessagePriority
{
public:
	/* This order should be change so the most important class to have a smaller value */
	static const unsigned int TimedAutomata = 1;
	static const unsigned int Transition = 1 << 1;
	static const unsigned int Template = 1 << 2;
	static const unsigned int Parser = 1 << 3;
	static const unsigned int Expression = 1 << 4;
	static const unsigned int Pin = 1 << 5;
	static const unsigned int Chan = 1 << 14;
	static const unsigned int Clock = 1 << 6;
	static const unsigned int State = 1 << 7;
	static const unsigned int SymbolTable = 1 << 8;
	static const unsigned int StringParser = 1 << 9;
	static const unsigned int ClockTable = 1 << 10;
	static const unsigned int ChanTable = 1 << 11;
	static const unsigned int Sync = 1 << 12;
	static const unsigned int LocalTable = 1 << 13;

	DebugMessagePriority() : priority{0} {}
	DebugMessagePriority(unsigned int p) 
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

	unsigned int operator&(const DebugMessagePriority& rhs)
	{
		return priority & rhs.getPriority();
	}

	void setPriority(unsigned int p)
	{
		priority = p;
	}

	unsigned int getPriority() const
	{
		return priority;
	}

private:
	unsigned int priority;
};

#endif