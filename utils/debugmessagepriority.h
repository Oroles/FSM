#ifndef _DEBUG_MESSAGE_PRIORITY_H_
#define _DEBUG_MESSAGE_PRIORITY_H_

#include <iostream>
/*
How to use:
	see file components/module.cpp for a call
	A higher value for priority equals a higher priority for the message
	All the message under or equal to currentPriority will be display
*/

/*
1. Expression
2. Chan
3. Clock
4. FSM
5, Module
6. State
7. SymbolTable
8. Tranzition
9. Parser
10. StringParser 
*/

class DebugMessagePriority
{
public:
	static const unsigned int Fsm = 1;
	static const unsigned int Tranzition = 1 << 1;
	static const unsigned int Module = 1 << 2;
	static const unsigned int Expression = 1 << 3;
	static const unsigned int Chan = 1 << 3; 
	static const unsigned int Clock = 1 << 4; 
	static const unsigned int State = 1 << 5;
	static const unsigned int SymbolTable = 1 << 6;
	static const unsigned int Parser = 1 << 7;
	static const unsigned int StringParser = 1 << 8;

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