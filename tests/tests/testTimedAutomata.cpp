#include <iostream>
#include <map>

#include "utils.h"
#include "../components/timedautomata.h"
#include "../components/transition.h"
#include "../components/state.h"

int main(int argc, char* argv[])
{
	TimedAutomata ta;
	{
		Template m1;
		m1.setCurrentState( State( "a" ) );
		m1.addTransition( Transition( State( "a" ), State( "b" ) ) );
		m1.addTransition( Transition( State( "b" ), State( "a" ) ) );
		m1.setName( "m1" );
		ta.addTemplate( m1 );
	}

	{
		Template m2;
		m2.setCurrentState( State( "a0" ) );
		m2.addTransition( Transition( State( "a0" ), State( "b1" ) ) );
		m2.addTransition( Transition( State( "b1" ), State( "a0" ) ) );
		m2.setName( "m2" );
		ta.addTemplate( m2 );
	}

	ta.step();
	ta.addSystems( std::map<std::string,std::string>
		{ {"Process1","m1"}, {"Process2","m2"}, {"Process3","m1"}, {"Process4","m3"} } );
	ta.step();

	return 0;
}