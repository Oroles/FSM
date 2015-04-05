#include <iostream>

#include "utils.h"
#include "../components/tranzition.h"
#include "../components/state.h"
#include "../expressions/expression.h"
#include "../expressions/sync.h"
#include "../tables/symboltable.h"

int main(int argc, char* argv[] )
{
	SymbolTable::getInstance().addEntries( std::vector<std::pair<std::string,int> >{ 
		std::pair<std::string,int>{ "a",1 },
		std::pair<std::string,int>{ "b",2 },
		std::pair<std::string,int>{ "c",3 } } );
	State a("a");
	State b("b");
	Tranzition tran(a,b);

	TEST_EQUAL( tran.getSource(), a );
	TEST_EQUAL( tran.getDestination(), b );

	{
		Tranzition aux = tran;
		TEST_EQUAL( aux.getSource(), a );
		TEST_EQUAL( aux.getDestination(), b );
		State state1( "c" );
		aux.setSource( state1 );
		TEST_EQUAL( aux.getSource(), state1 );
		aux.setDestination( state1 );
		TEST_EQUAL( aux.getDestination(), state1 );
	}

	tran.setModuleName( "Process" );
	TEST_EQUAL( tran.getModuleName(), "Process" );

	/* Test isAvailable */
	IS_TRUE( tran.isAvailable( a ) );
	IS_FALSE( tran.isAvailable( b ) );
	tran.addGuard( Expression("2 < 3") );
	IS_TRUE( tran.isAvailable( a ) );
	IS_FALSE( tran.isAvailable( b ) );

	/* Test operator() */
	TEST_EQUAL( tran.operator()( a ), b );
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 1 );
	tran.addUpdate( Expression( "a = 2" ) );
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 1 );
	TEST_EQUAL( tran.operator()( a ), b );
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 2 );

	/* Test isSync */
	IS_TRUE( tran.isSync() );
	tran.setSync( Sync("c!") );
	IS_FALSE( tran.isSync() );

	tran.setSync( Sync("") );
	IS_TRUE( tran.isSync() );

	/* Test guard */
	IS_TRUE( tran.isAvailable( a ) );
	tran.addGuard( Expression("a == 2") );
	IS_TRUE( tran.isAvailable( a ) );
	SymbolTable::getInstance().setValue( "a", 1 );
	IS_FALSE( tran.isAvailable( a ) );
	SymbolTable::getInstance().setValue( "a", 2 );
	IS_TRUE( tran.isAvailable( a ) );

	return 0;
}