#include <iostream>
#include <map>

#include "utils.h"
#include "../components/timedautomata.h"
#include "../components/edge.h"
#include "../components/location.h"

int main(int argc, char* argv[])
{
	TimedAutomata ta;
	{
		Template m1;
		m1.setCurrentState( Location( "a" ) );
		m1.addTransition( Edge( Location( "a" ), Location( "b" ) ) );
		m1.addTransition( Edge( Location( "b" ), Location( "a" ) ) );
		m1.setName( "m1" );
		ta.addTemplate( m1 );
	}

	{
		Template m2;
		m2.setCurrentState( Location( "a0" ) );
		m2.addTransition( Edge( Location( "a0" ), Location( "b1" ) ) );
		m2.addTransition( Edge( Location( "b1" ), Location( "a0" ) ) );
		m2.setName( "m2" );
		ta.addTemplate( m2 );
	}

	ta.step();
	ta.addSystems( std::map<std::string,std::string>
		{ {"Process1","m1"}, {"Process2","m2"}, {"Process3","m1"}, {"Process4","m3"} } );
	ta.step();

	return 0;
}