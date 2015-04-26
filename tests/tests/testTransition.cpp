#include <iostream>

#include "utils.h"
#include "../components/transition.h"
#include "../components/state.h"
#include "../expressions/expression.h"
#include "../expressions/sync.h"
#include "../tables/symboltable.h"
#include "../utils/utils.h"

int main(int argc, char* argv[] )
{
	SymbolTable::getInstance().addEntries( std::vector<std::pair<std::string,int> >{ 
		std::pair<std::string,int>{ "a",1 },
		std::pair<std::string,int>{ "b",2 },
		std::pair<std::string,int>{ "c",3 } } );
	State a("a");
	State b("b");
	Transition tran(a,b);

	TEST_EQUAL( tran.getSource(), a );
	TEST_EQUAL( tran.getDestination(), b );

	{
		Transition aux = tran;
		TEST_EQUAL( aux.getSource(), a );
		TEST_EQUAL( aux.getDestination(), b );
		State state1( "c" );
		aux.setSource( state1 );
		TEST_EQUAL( aux.getSource(), state1 );
		aux.setDestination( state1 );
		TEST_EQUAL( aux.getDestination(), state1 );
	}

	/* Test isAvailable */
	TEST_EQUAL( TranzactionAvailableStatus::Available,  tran.isAvailable( a ) );
	TEST_EQUAL( TranzactionAvailableStatus::NotSource, tran.isAvailable( b ) );
	tran.addGuard( Expression("2 < 3") );
	TEST_EQUAL( TranzactionAvailableStatus::Available, tran.isAvailable( a ) );
	TEST_EQUAL( TranzactionAvailableStatus::NotSource, tran.isAvailable( b ) );

	/* Test operator() */
	TEST_EQUAL( tran.operator()( a ), b );
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 1 );
	tran.addUpdate( Expression( "a = 2" ) );
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 1 );
	TEST_EQUAL( tran.operator()( a ), b );
	SymbolTable::getInstance().updateSymbols();
	TEST_EQUAL( SymbolTable::getInstance().getValue("a"), 2 );

	/* Test isSync */ 
	IS_TRUE( tran.isSync() );
	tran.setSync( Sync("c!") );
	IS_FALSE( tran.isSync() );

	tran.setSync( Sync("") );
	IS_TRUE( tran.isSync() );

	/* Test guard */
	TEST_EQUAL( TranzactionAvailableStatus::Available,  tran.isAvailable( a ) );
	tran.addGuard( Expression("a == 2") );
	TEST_EQUAL( TranzactionAvailableStatus::Available, tran.isAvailable( a ) );
	SymbolTable::getInstance().setValue( "a", 1 );
	SymbolTable::getInstance().updateSymbols();
	TEST_EQUAL( TranzactionAvailableStatus::NotGuard, tran.isAvailable( a ) );
	SymbolTable::getInstance().setValue( "a", 2 );
	SymbolTable::getInstance().updateSymbols();
	TEST_EQUAL( TranzactionAvailableStatus::Available,  tran.isAvailable( a ) );
	return 0;
}
