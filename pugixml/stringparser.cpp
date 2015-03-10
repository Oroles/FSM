#include "stringparser.h"

#include "../components/variables/clock.h"
#include "../components/variables/chan.h"

#include <regex>
#include <map>
#include <iostream>

std::map<std::string,std::regex> regex = { { "chan", std::regex("(chan)( [a-zA-Z]+)(;)") },
										   { "clock", std::regex("(clock)( [a-zA-Z]+)(;)") }  };

StringParser::StringParser(std::string t) : text(t)
{
	assert(t.size() != 0);
	dispatcher["chan"] = &StringParser::generateChan;
	dispatcher["clock"] = &StringParser::generateClock;
}

std::vector<std::shared_ptr<Variable>> StringParser::generateVariables()
{
	std::vector<std::shared_ptr<Variable>> rez;
	for ( auto rgx : regex )
	{
		auto words_begin = std::sregex_iterator(text.begin(), text.end(), rgx.second );
		auto words_end = std::sregex_iterator();

		for ( std::sregex_iterator i = words_begin; i != words_end; ++i )
		{
			std::string matchString = i->str();
			rez.push_back( (this->*dispatcher[rgx.first])( matchString ) );
		}
	}
	return rez;
}

std::shared_ptr<Variable> StringParser::generateClock(std::string name)
{
	std::shared_ptr<Variable> rez(new Clock(name,0));
	return rez;
}

std::shared_ptr<Variable> StringParser::generateChan(std::string name)
{
	std::shared_ptr<Variable> rez(new Chan(name,0));
	return rez;
}