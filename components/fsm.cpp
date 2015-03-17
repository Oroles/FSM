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
	//Update clocks Work around
	for ( auto& c : clocks )
	{
		c.setValue( SymbolTable::getInstance().getEntry( c.getName() ) );
	}

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
	display(DebugMessagePriority::Fsm, "There were added ", c.size(), "clocks to FSM\n" );
	for( auto& v : c )
	{
		display(DebugMessagePriority::Fsm, "The ", v, "is added to Symbol Table\n");
		SymbolTable::getInstance().updateEntry(v.getName(),v.getValue());
	}
	clocks = c;
}

void FSM::addChannels(const std::vector<Chan>& c)
{
	display(DebugMessagePriority::Fsm, "There were added ", c.size(), "channels to FSM\n" );
	for ( auto& v : c )
	{
		display(DebugMessagePriority::Fsm, "The ", v, "is added to Symbol Table\n");
		SymbolTable::getInstance().updateEntry(v.getName(),v.getValue());
	}
	channels = c;
}

void FSM::addTemplate(const Module& t)
{
	templates.push_back( t );
}

void FSM::addModules(const std::map<std::string,std::string> modulesName )
{
	for ( auto name : modulesName )
	{
		for ( auto& t : templates )
		{
			if ( t.getName() == name.second )
			{
				Module aux = t;
				aux.setName( name.first );
				modules.push_back( aux );
			}
		}
	}
}