#include <iostream>

#include "components/state.h"

int main( int argc, char* argv[] )
{
	State s("ana");
	State s1;
	State s2( "maria" );
	State s3( s );

	/* Test constructors & equal operator */
	if ( s == s1 ) return -1;
	if ( s == s2 ) return -1;
	if ( s1 == s2 ) return -1;
	if ( !( s == s3 ) ) return -1;

	/* Test operator != */
	if ( s != s3 ) return -1;
	if ( !( s != s1 ) ) return -1;

	/* Test assign operator */
	s1 = s;
	if ( !( s1 == s ) ) return -1;
	if ( s1 == s2  ) return -1;
	if ( !( s1 == s3 ) ) return -1;

	/* Test set and get name */
	if ( s1.getName() != "ana" ) return -1;
	if ( s.getName() != "ana" ) return -1;
	if ( s2.getName() != "maria" ) return -1;
	if ( s3.getName() != "ana" ) return -1;
	s1.setName( "testName" );
	if ( s1.getName() != "testName" ) return -1;
	if ( s.getName() != "ana" ) return -1;

	return 0;
}