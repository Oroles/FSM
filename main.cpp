#include <iostream>
#include <string>
#include <algorithm>
#include <wiringPi.h>

#include "components/timedautomata.h"
#include "pugixml/parser.h"
#include "utils/utils.h"


int main(int argc, char* argv[])
{

#ifdef RASPBERRY_PI
	wiringPiSetup();
#endif

	std::vector<std::string> arguments;
	for ( int i = 0; i < argc; ++i)
	{
		arguments.push_back( argv[i] );
	}
	setPriority( arguments );
	std::string fileName = getFileName( arguments );
	setStepProgress( arguments );
	setQuit( arguments );

	TimedAutomata fsm;
	Parser parser(fileName);
	parser.generateFSM(&fsm);

	if ( quitApp == false )
	{
		while( 1 )
		{
			fsm.step();
		}
	}
	return 0;
}