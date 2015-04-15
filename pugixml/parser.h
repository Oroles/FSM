#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#include "../components/timedautomata.h"
#include "../components/module.h"
#include "../components/state.h"
#include "../components/transition.h"
#include "../expressions/expression.h"
#include "pugixml.hpp"

class Parser
{
public:
	Parser(std::string name)
	{
		assert(name.size() != 0);
		pugi::xml_parse_result rez = doc.load_file(name.c_str());
		assert(rez.description() == std::string("No error"));
	}

	void generateFSM(TimedAutomata* fsm);

private:
	Module processTemplate(const pugi::xml_node& node );
	State processCurrentState(const pugi::xml_node& node);
	Transition processTransition(const pugi::xml_node& node);
	std::string processName(const pugi::xml_node& node );
	void processLabels(Transition* t, const pugi::xml_node& node );
	
	pugi::xml_document doc;
};

#endif