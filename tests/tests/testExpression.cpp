#include <iostream>
#include "../expressions/expression.h"
#include "../tables/symboltable.h"
#include "../tables/clocktable.h"
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
	{
		Expression ex( "1 <= 3" );
		IS_TRUE( ex.evaluate() );
	}
	{
		Expression ex( "2< = 1" );
		IS_FALSE( ex.evaluate() );
	}
	{
		Expression ex ( "2 <    = 2" ); /* It is normal? */
		IS_TRUE( ex.evaluate() ); 
	}
	{
		Expression ex ( " 3 > 2 " );
		IS_TRUE( ex.evaluate() );
	}
	{
		Expression ex ( " 1 >  2 " );
		IS_FALSE( ex.evaluate() );
	}
	{
		Expression ex ( "1 >= 1 " );
		IS_TRUE( ex.evaluate() );
	}
	{
		Expression ex (" 1 >= 2 " );
		IS_FALSE( ex.evaluate() );
	}
	{
		Expression ex ( " 2 != 1 " );
		IS_TRUE( ex.evaluate() );
	}
	{
		Expression ex ( "2 != 2 " );
		IS_FALSE( ex.evaluate() );
	}
	{
		SymbolTable::getInstance().setValue("a",2);
		Expression ex ( "a := 3" );
		TEST_NOT_EQUAL( SymbolTable::getInstance().getValue("a"), 3);
		IS_TRUE( ex.evaluate() );
		TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 3 );
	}
	{
		SymbolTable::getInstance().setValue("b",2);
		Expression ex( "b = 3" );
		TEST_NOT_EQUAL( SymbolTable::getInstance().getValue("a"), 2 );
		IS_TRUE( ex.evaluate() );
		TEST_EQUAL( SymbolTable::getInstance().getValue("b"), 3 );
	}
	{
		ClockTable::getInstance().addEntry( Clock( std::string("clock c;" ), 0 ) );
		Expression ex ( "c = 1");
		TEST_NOT_EQUAL( ClockTable::getInstance().getValue("c"), 1);
		TEST_EQUAL( ClockTable::getInstance().getValue("c"), 0);
		IS_TRUE( ex.evaluate() );
		ClockTable::getInstance().updateClocks();
		TEST_EQUAL( ClockTable::getInstance().getValue("c"), 1 );
	}
	{
		Expression ex( " 1 != 3 ");
		TEST_EQUAL( ex.getFirst(), "1" );
		TEST_EQUAL( ex.getSecond(), "3" );
		TEST_EQUAL( ex.getOp(), "!=" );
	}
	{
		Expression ex( " 2 <   1 " );
		TEST_EQUAL( ex.getFirst(), "2" );
		TEST_EQUAL( ex.getSecond(), "1" );
		TEST_EQUAL( ex.getOp(), "<" );
	}
	{
		Expression ex( " 0 >=  1 " );
		TEST_EQUAL( ex.getFirst(), "0" );
		TEST_EQUAL( ex.getSecond(), "1" );
		TEST_EQUAL( ex.getOp(), ">=" );
	}
	return 0;
}