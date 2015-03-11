#include "stringparser.h"

#include <regex>
#include <map>
#include <iostream>

std::map<std::string,std::regex> regex = { { "chan", std::regex("(chan)( [a-zA-Z]+)(;)") },
										   { "clock", std::regex("(clock)( [a-zA-Z]+)(;)") }  };

StringParser::StringParser(std::string t) : text(t)
{
	assert(t.size() != 0);
}


/* It should be a template */
std::vector<Clock> StringParser::generateClocks()
{
	std::vector<Clock> rez;
	auto words_begin = std::sregex_iterator(text.begin(), text.end(), regex["clock"] );
	auto words_end = std::sregex_iterator();

	for ( std::sregex_iterator i = words_begin; i != words_end; ++i )
	{
		std::string matchString = i->str();
		rez.push_back( Clock(matchString) );
	}
	return rez;
}

std::vector<Chan> StringParser::generateChannels()
{
	std::vector<Chan> rez;
	auto words_begin = std::sregex_iterator(text.begin(), text.end(), regex["chan"] );
	auto words_end = std::sregex_iterator();

	for ( std::sregex_iterator i = words_begin; i != words_end; ++i )
	{
		std::string matchString = i->str();
		rez.push_back( Chan(matchString) );
	}
	return rez;
}