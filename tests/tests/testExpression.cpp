#include <iostream>
#include "../expressions/expression.h"
#include "../tables/symboltable.h"
#include "../tables/clocktable.h"
#include "utils.h"


int main( int argc, char* argv[] )
{
	SymbolTable::getInstance().addEntries( std::vector<std::pair<std::string,int> >{ 
		std::pair<std::string,int>{ "a",1 },
		std::pair<std::string,int>{ "b",2 },
		std::pair<std::string,int>{ "c",3 } } );
	{
		Expression ex( "a < 4" );
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex( "a > 4" );
		IS_FALSE( ex.evaluate() );
	}

	{
		Expression ex( "a >= 4");
		IS_FALSE( ex.evaluate() );
	}

	{
		Expression ex( "a <= 4");
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex( "a == 3" );
		IS_FALSE( ex.evaluate() );
	}

	{
		Expression ex( "a != 3" );
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex( "a << 1" );
		TEST_EQUAL( ex.evaluate(), 2 );
	}

	{
		Expression ex( "c >> 1" );
		TEST_EQUAL( ex.evaluate(), 1 );
	}

	{
		Expression ex ( "b == 2 * 1" );
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex ( "a == 2 - 1" );
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex( "c = 2 + 1" );
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex( "c = 9 / 3" );
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex( "a == 3 % 2");
		IS_TRUE( ex.evaluate() );
	}

	{
		Expression ex( "a = b");
		TEST_EQUAL( ex.evaluate(), 2 );
	}

	{
		Expression ex( "a := 1" );
		TEST_EQUAL( ex.evaluate(), 1 );
	}

	{
		Expression ex( "a += 3" );
		TEST_EQUAL( ex.evaluate(), 4 );
	}

	{
		Expression ex( "a -= 3" );
		TEST_EQUAL( ex.evaluate(), 1 );
	}

	{
		Expression ex( "a *= 2" );
		TEST_EQUAL( ex.evaluate(), 2 );
	}

	{
		Expression ex( "a /= 2" );
		TEST_EQUAL( ex.evaluate(), 1 );
	}

	{
		Expression ex( "a <<= 2" );
		TEST_EQUAL( ex.evaluate(), 4 );
	}

	{
		Expression ex( "a >>= 2" );
		TEST_EQUAL( ex.evaluate(), 1 );
	}

	{
		Expression ex ( "a = 3 + 2 * 5");
		TEST_EQUAL( ex.evaluate(), 13 );
	}

	{
		Expression ex ( "a = ( 3 + 2 ) * 5" );
		TEST_EQUAL( ex.evaluate(), 25 );
	}

	{
		Expression ex ( "a = ( a / 5 ) % ( 2 + 2 )");
		TEST_EQUAL( ex.evaluate(), 1 );
	}

	return 0;
}