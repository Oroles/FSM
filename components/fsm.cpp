#include "fsm.h"
#include "../tables/clocktable.h"
#include "../tables/localtable.h"
#include "../utils/utils.h"

void FSM::step()
{
	for ( auto& m : modules )
	{
		m.step();
	}
	ClockTable::getInstance().updateClocks();
	nextStep();
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
				LocalTable::getInstance().generateTables( name.second, name.first );
			}
		}
	}
}