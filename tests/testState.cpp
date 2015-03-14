#include <iostream>

#include "components/state.h"

int main( int argc, char* argv[] )
{
	State s("ana");
	State s1;

	if ( s == s1 )
	{
		return -1;
	}

	if ( s.getName() != "ana" )
	{
		return -1;
	}

	return 0;
}