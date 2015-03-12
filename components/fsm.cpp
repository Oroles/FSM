#include "fsm.h"
#include "symboltable.h"
#include "../utils/utils.h"

#include <thread>

void FSM::step()
{
	for ( auto& m : modules )
	{
		m.step();
	}
	nextStep();
	for ( auto& c : clocks )
	{
		c.update();
		SymbolTable::getInstance().updateEntry(c.getName(),c.getValue());
	}
}

void FSM::startModules()
{
	std::vector<std::thread> threads;
	for ( auto m : modules )
	{
		threads.push_back( std::thread(&Module::run, m) );
	}

	for ( std::vector<std::thread>::size_type i = 0; i < threads.size(); ++i )
	{
		threads[i].join();
	}
}

void FSM::addClocks(const std::vector<Clock>& c)
{
	display(DebugMessagePriority::Priority::Level1, "There were added ", c.size(), "clocks to FSM\n" );
	for( auto& v : c )
	{
		display(DebugMessagePriority::Priority::Level1, "The ", v, "is added to Symbol Table\n");
		SymbolTable::getInstance().updateEntry(v.getName(),v.getValue());
	}
	clocks = c;
}

void FSM::addChannels(const std::vector<Chan>& c)
{
	display(DebugMessagePriority::Priority::Level1, "There were added ", c.size(), "channels to FSM\n" );
	for ( auto& v : c )
	{
		display(DebugMessagePriority::Priority::Level1, "The ", v, "is added to Symbol Table\n");
		SymbolTable::getInstance().updateEntry(v.getName(),v.getValue());
	}
	channels = c;
}

void FSM::addModule(const Module& m)
{
	modules.push_back( m );
}