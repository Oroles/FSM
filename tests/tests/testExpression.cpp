#include <iostream>
#include "../expressions/expression.h"
#include "utils.h"


int main( int argc, char* argv[] )
{
	{
		Expression ex( "1 < 2" );
		IS_TRUE( ex.evaluate() );
	}
	{
		Expression ex( " 1 < 3" );
		IS_TRUE( ex.evaluate() );
	}
	return 0;
}