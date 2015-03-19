#include "stringparser.h"

#include <regex>
#include <map>
#include <iostream>

std::map<std::string,std::regex> regex = { { "chan", std::regex("(chan)( [a-zA-Z]+)(;)") },
										   { "clock", std::regex("(clock)( [a-zA-Z]+)(;)") },
										   { "decl", std::regex("([a-zA-Z1-9]+)( ?)(=)( ?)([a-zA-Z]+)") },
										   { "declName", std::regex("( ?)[a-zA-Z1-9]+")}  };

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
		rez.push_back( Clock(matchString,0) );
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

std::map<std::string,std::string> StringParser::generateModules()
{
	std::map<std::string,std::string> rez;
	auto words_begin = std::sregex_iterator(text.begin(), text.end(), regex["decl"] );
	auto words_end = std::sregex_iterator();

	for ( std::sregex_iterator i = words_begin; i != words_end; ++i )
	{
		std::string matchString = i->str();
		auto poz = matchString.find_last_of(" ");
		std::string type = matchString.substr( poz + 1, std::string::npos );
		poz = matchString.find(" ");
		std::string name = matchString.substr( 0, poz );
		rez.emplace(name,type);
	}
	return rez;
}