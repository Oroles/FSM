#include "timedautomata.h"
#include "../tables/clocktable.h"
#include "../tables/localtable.h"
#include "../tables/symboltable.h"
#include "../tables/pintable.h"
#include "../utils/utils.h"

void TimedAutomata::step()
{
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
}

void TimedAutomata::addTemplate(const Template& t)
{
	templates.push_back( t );
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