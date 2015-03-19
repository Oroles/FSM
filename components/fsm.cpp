#include "fsm.h"
#include "../tables/clocktable.h"
#include "../utils/utils.h"

#include <thread>

void FSM::step()
{
	for ( auto& m : modules )
	{
		m.step();
	}
	ClockTable::getInstance().updateClocks();
	nextStep();
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