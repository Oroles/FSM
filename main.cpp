#include <iostream>
#include <string>
#include <algorithm>

#include "components/fsm.h"
#include "pugixml/parser.h"
#include "utils/utils.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> arguments;
	for ( int i = 0; i < argc; ++i)
	{
		arguments.push_back( argv[i] );
	}
	setPriority( arguments );
	std::string fileName = getFileName( arguments );
	setStepProgress( arguments );

	FSM fsm;
	Parser parser(fileName);
	parser.generateFSM(&fsm);
	while( 1 )
	{
		fsm.step();
	}
	return 0;
}