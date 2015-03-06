#include <iostream>

#include "components/fsm.h"
#include "pugixml/parser.h"

int main(int argc, char* argv[])
{
	FSM fsm;
	Parser parser("SimpleStates.xml");
	parser.generateFSM(&fsm);
	return 0;
}