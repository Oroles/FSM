#include <iostream>

#include "utils.h"
#include "../components/template.h"
#include "../components/transition.h"
#include "../components/state.h"

int main( int argc, char* argv[] )
{
	Template m;
	TEST_EQUAL( m.getName(), "" );
	m.setName( "Process" );
	TEST_EQUAL( m.getName(), "Process" );

	TEST_EQUAL( m.nextState( State( "a" ) ), State( "a" ) );
	m.setCurrentState( State( "b" ) );
	TEST_EQUAL( m.nextState( State( "b" ) ), State( "b" ) );
	m.addTransition( Transition(State( "b" ) , State( "a" ) ) );
	TEST_EQUAL( m.nextState( State( "b" ) ), State( "a" ) );

	m.step();
	TEST_EQUAL( m.nextState( State( "a" ) ), State( "a" ) );
	m.setCurrentState( State( "b" ) );
	TEST_EQUAL( m.nextState( State( "b" ) ), State( "a" ) );

	m.addTransition( Transition( State( "b" ), State( "c" ) ) );
	TEST_EQUAL( m.nextState( State( "b" ) ), State( "a" ) );
	m.addTransition( Transition( State( "a" ), State( "b" ) ) );
	TEST_EQUAL( m.nextState( State( "a" ) ), State( "b" ) );

	{
		Template m1 = m;
		TEST_EQUAL( m1.nextState( State( "b" ) ), State( "a" ) );
		TEST_EQUAL( m1.nextState( State( "a" ) ), State( "b" ) );
		TEST_EQUAL( m1.nextState( State( "c") ), State( "c" ) );
	}

	{
		Template m1;
		m1 = m;
		TEST_EQUAL( m1.nextState( State( "b" ) ), State( "a" ) );
		TEST_EQUAL( m1.nextState( State( "a" ) ), State( "b" ) );
		TEST_EQUAL( m1.nextState( State( "c") ), State( "c" ) );
	}

	return 0;
}