#include "fsm.h"

#include <thread>

void FSM::step()
{
	for ( auto m : modules )
	{
		m.step();
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