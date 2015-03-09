#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <cassert>
#include <memory>
#include <map>
#include <vector>

#include "../components/variables/variable.h"

class StringParser
{
public:
	StringParser( std::string t );
	std::vector<std::shared_ptr<Variable>> generateVariables();

private:
	using genVar = std::shared_ptr<Variable> (StringParser::*)(const std::string);
	std::map<std::string,genVar> dispatcher;

	std::shared_ptr<Variable> generateClock(std::string name);
	std::shared_ptr<Variable> generateChan(std::string name);

	std::string text;
};

#endif