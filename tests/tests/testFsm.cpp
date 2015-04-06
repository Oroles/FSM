#include <iostream>
#include <map>

#include "utils.h"
#include "../components/fsm.h"
#include "../components/tranzition.h"
#include "../components/state.h"

int main(int argc, char* argv[])
{
	FSM fsm;
	{
		Module m1;
		m1.setCurrentState( State( "a" ) );
		m1.addTranzition( Tranzition( State( "a" ), State( "b" ) ) );
		m1.addTranzition( Tranzition( State( "b" ), State( "a" ) ) );
		m1.setName( "m1" );
		fsm.addTemplate( m1 );
	}

	{
		Module m2;
		m2.setCurrentState( State( "a0" ) );
		m2.addTranzition( Tranzition( State( "a0" ), State( "b1" ) ) );
		m2.addTranzition( Tranzition( State( "b1" ), State( "a0" ) ) );
		m2.setName( "m2" );
		fsm.addTemplate( m2 );
	}

	fsm.step();
	fsm.addModules( std::map<std::string,std::string>
		{ {"Process1","m1"}, {"Process2","m2"}, {"Process3","m1"}, {"Process4","m3"} } );
	fsm.step();

	return 0;
}