#include <iostream>

#include "utils.h"
#include "../components/tranzition.h"
#include "../components/state.h"
#include "../expressions/expression.h"
#include "../expressions/sync.h"

int main(int argc, char* argv[] )
{
	State a("a");
	State b("b");
	Tranzition tran(a,b);

	TEST_EQUAL( tran.getSource(), a );
	return 0;
}