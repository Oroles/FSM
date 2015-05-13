#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>

#include "../components/timedautomata.h"
#include "../components/template.h"
#include "../components/location.h"
#include "../components/edge.h"
#include "../expressions/expression.h"
#include "pugixml.hpp"

class Parser
{
public:
	class InvalidFile : public std::exception{
	public:
		virtual const char* what() const throw()
		{
			return "Invalid input file";
		}
	};

	Parser(std::string name)
	{
		assert(name.size() != 0);
		pugi::xml_parse_result rez = doc.load_file(name.c_str());

		if ( rez.description() != std::string("No error"))
		{
			throw InvalidFile();
		}
		assert(rez.description() == std::string("No error"));
	}

	void generateFSM(TimedAutomata* fsm);

private:
	Template processTemplate(const pugi::xml_node& node );
	Location processCurrentState(const pugi::xml_node& node);
	Edge processTransition(const pugi::xml_node& node);
	std::string processName(const pugi::xml_node& node );
	void processLabels(Edge* t, const pugi::xml_node& node );
	
	pugi::xml_document doc;
	std::vector<Location> templateLocations;
};

#endif