#include <iostream>

#include "utils.h"
#include "../components/module.h"
#include "../components/tranzition.h"
#include "../components/state.h"

int main( int argc, char* argv[] )
{
	Module m;
	TEST_EQUAL( m.getName(), "" );
	m.setName( "Process" );
	TEST_EQUAL( m.getName(), "Process" );

	return 0;
}