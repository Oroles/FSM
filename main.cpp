#include <iostream>
#include <string>
#include <algorithm>
#include <wiringPi.h>
#include <thread>
#include <exception>

#include "components/timedautomata.h"
#include "xmlparser/parser.h"
#include "utils/utils.h"

std::string stopCondition = "";

void readData()
{
	std::cin >> stopCondition;
}

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
	bool step = setStepProgress( arguments );
	setQuit( arguments );

	TimedAutomata fsm;
	try
	{
		Parser parser(fileName);
		parser.generateFSM(&fsm);
	}
	catch( std::exception& e )
	{
		std::cout << e.what() << std::endl;
		return -1;
	}


	if ( quitApp == false )
	{
		if ( step != true )
		{
			std::thread t(readData);
			while( stopCondition != "quit" )
			{
				fsm.step();
			}
			t.join();
		}
		else
		{
			while( 1 )
			{
				fsm.step();
			}
		}
	}

	return 0;
}