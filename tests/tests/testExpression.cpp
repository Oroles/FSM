#include <iostream>
#include "../expressions/expression.h"
#include "utils.h"


int main( int argc, char* argv[] )
{
	Expression ex1( "1 < 2" );
	IS_TRUE( ex1.evaluate() );
	return 0;
}