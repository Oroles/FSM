#include <iostream>
#include <algorithm>

#include "components/fsm.h"
#include "pugixml/parser.h"
#include "utils/utils.h"

extern bool allowDebug;

int main(int argc, char* argv[])
{
	std::vector<std::string> arguments;
	for ( int i = 0; i < argc; ++i)
	{
		arguments.push_back( argv[i] );
	}

	std::for_each(arguments.begin(), arguments.end(), [&](std::string arg){ if (arg=="-d") { allowDebug=true; } } );

	FSM fsm;
	Parser parser("SimpleStates.xml");
	parser.generateFSM(&fsm);
	fsm.step();
	return 0;
}