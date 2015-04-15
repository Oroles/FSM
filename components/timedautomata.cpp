#include "timedautomata.h"
#include "../tables/clocktable.h"
#include "../tables/localtable.h"
#include "../tables/symboltable.h"
#include "../tables/pintable.h"
#include "../utils/utils.h"

void TimedAutomata::step()
{
	for ( auto& m : modules )
	{
		m.step();
	}
	ClockTable::getInstance().updateClocks();
	SymbolTable::getInstance().updateSymbols();
	PinTable::getInstance().updatePins();
	nextStep();
}

void TimedAutomata::addTemplate(const Module& t)
{
	templates.push_back( t );
}

void TimedAutomata::addModules(const std::map<std::string,std::string> modulesName )
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
				LocalTable::getInstance().generateTables( name.second, name.first );
			}
		}
	}
}