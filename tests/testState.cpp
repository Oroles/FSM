#include <iostream>

#include "components/state.h"

#include "utils.h"

int main( int argc, char* argv[] )
{
	State s("ana");
	State s1;
	State s2( "maria" );
	State s3( s );

	/* Test constructors & equal operator */
	TEST_NOT_EQUAL(s,s1);
	TEST_NOT_EQUAL(s,s2);
	TEST_NOT_EQUAL(s1,s2);
	TEST_EQUAL(s,s3);

	/* Test assign operator */
	s1 = s;
	TEST_EQUAL(s1,s);
	TEST_NOT_EQUAL(s1,s2);
	TEST_EQUAL(s1,s3);

	/* Test set and get name */
	if ( s1.getName() != "ana" ) FAILED_BLOCK();
	if ( s.getName() != "ana" ) FAILED_BLOCK();
	if ( s2.getName() != "maria" ) FAILED_BLOCK();
	if ( s3.getName() != "ana" ) FAILED_BLOCK();
	s1.setName( "testName" );
	if ( s1.getName() != "testName" ) FAILED_BLOCK();
	if ( s.getName() != "ana" ) FAILED_BLOCK();

	return 0;
}