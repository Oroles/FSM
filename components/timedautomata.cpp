#include "timedautomata.h"
#include "../tables/clocktable.h"
#include "../tables/localtable.h"
#include "../tables/symboltable.h"
#include "../tables/pintable.h"
#include "../utils/utils.h"

#include <chrono>
#include <thread>

void TimedAutomata::step()
{
	auto startTime = std::chrono::high_resolution_clock::now();
	for ( auto& m : systems )
	{
		m.step();
	}

	for ( auto& m : systems )
	{
		m.resetStepFlag();
	}

	ClockTable::getInstance().updateClocks();
	SymbolTable::getInstance().updateSymbols();
	PinTable::getInstance().updatePins();
	nextStep();

	auto endTime = std::chrono::high_resolution_clock::now();
	int totalTime = std::chrono::duration_cast<std::chrono::milliseconds>( endTime - startTime ).count();

	if ( period < 0 )
	{
		return;
	}
	else
	{
		if ( totalTime > period )
		{
			//throw exception, the runtime exceed the period
			throw UnscheduleSystem();
		}
		else
		{
			//find out how much it has to sleep
			int timeToSleep = period - totalTime;
			std::this_thread::sleep_for(std::chrono::milliseconds(timeToSleep));
		}
	}
}

void TimedAutomata::addTemplate(const Template& t)
{
	templates.push_back( t );
}

void TimedAutomata::setPeriod(int p)
{
	period = p;
}

void TimedAutomata::addSystems(const std::map<std::string,std::string> systemsName )
{
	for ( auto name : systemsName )
	{
		for ( auto& t : templates )
		{
			if ( t.getName() == name.second )
			{
				Template aux = t;
				aux.setName( name.first );
				systems.push_back( aux );
				LocalTable::getInstance().generateTables( name.second, name.first );
			}
		}
	}
	//Makes the dependency table
	for ( auto& t : systems )
	{
		t.setObserver( &obs );
		obs.addObservable( &t );
	}
}

void TimedAutomata::closeDevices()
{
	PinTable::getInstance().closeAllDevices();
}