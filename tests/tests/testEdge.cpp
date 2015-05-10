#include <iostream>

#include "utils.h"
#include "../components/edge.h"
#include "../components/location.h"
#include "../expressions/expression.h"
#include "../tables/symboltable.h"
#include "../utils/utils.h"
#include "../utils/plaindata.h"

int main(int argc, char* argv[] )
{
	SymbolTable::getInstance().addEntries( std::vector<PlainData >{ 
		PlainData{ "a",1,1 },
		PlainData{ "b",1,2 },
		PlainData{ "c",1,3 } } );
	Location a("a");
	Location b("b");
	Edge tran(a,b);

	TEST_EQUAL( tran.getSource(), a );
	TEST_EQUAL( tran.getDestination(), b );

	{
		Edge aux = tran;
		TEST_EQUAL( aux.getSource(), a );
		TEST_EQUAL( aux.getDestination(), b );
		Location state1( "c" );
		aux.setSource( state1 );
		TEST_EQUAL( aux.getSource(), state1 );
		aux.setDestination( state1 );
		TEST_EQUAL( aux.getDestination(), state1 );
	}

	/* Test isAvailable */
	TEST_EQUAL( TransitionAvailableStatus::Available,  tran.isAvailable( a ) );
	TEST_EQUAL( TransitionAvailableStatus::NotSource, tran.isAvailable( b ) );
	tran.addGuard( Expression("2 < 3") );
	TEST_EQUAL( TransitionAvailableStatus::Available, tran.isAvailable( a ) );
	TEST_EQUAL( TransitionAvailableStatus::NotSource, tran.isAvailable( b ) );

	/* Test operator() */
	TEST_EQUAL( tran.operator()( a ), b );
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 1 );
	tran.addUpdate( Expression( "a = 2" ) );
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 1 );
	TEST_EQUAL( tran.operator()( a ), b );
	SymbolTable::getInstance().updateSymbols();
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 2 );

	/* Test guard */
	TEST_EQUAL( TransitionAvailableStatus::Available,  tran.isAvailable( a ) );
	tran.addGuard( Expression("a == 2") );
	TEST_EQUAL( TransitionAvailableStatus::Available, tran.isAvailable( a ) );
	SymbolTable::getInstance().setValue( "a", 1 );
	SymbolTable::getInstance().updateSymbols();
	TEST_EQUAL( TransitionAvailableStatus::NotGuard, tran.isAvailable( a ) );
	SymbolTable::getInstance().setValue( "a", 2 );
	SymbolTable::getInstance().updateSymbols();
	TEST_EQUAL( TransitionAvailableStatus::Available,  tran.isAvailable( a ) );
	return 0;
}
