#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#include "../components/fsm.h"
#include "../components/module.h"
#include "../components/state.h"
#include "../components/tranzition.h"
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

	void generateFSM(FSM* fsm);

private:
	Module processModule(const pugi::xml_node& node );
	State processState(const pugi::xml_node& node );
	State processCurrentState(const pugi::xml_node& node);
	Tranzition processTranzition(const pugi::xml_node& node);
	std::string processName(const pugi::xml_node& node );
	std::vector<Expression> processGuards(const pugi::xml_node& node);
	std::vector<std::string> processSyncs(const pugi::xml_node& node);

	pugi::xml_document doc;
};

#endif