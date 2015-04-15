#include "stringparser.h"

#include "../utils/utils.h"

#include <regex>
#include <map>
#include <iostream>

std::map<std::string,std::regex> regex = { { "chan", std::regex("(chan)( [a-zA-Z0-9_]+)(;)") },
										   { "clock", std::regex("(clock)( [a-zA-Z0-9_]+)(;)") },
										   { "decl", std::regex("([a-zA-Z0-9_]+)( ?)(=)( ?)([a-zA-Z0-9_]+)") },
										   { "declVar", std::regex("(int)( ?)([a-zA-Z0-9_]+)(;)") },
										   { "defVar", std::regex("(int)( ?)([a-zA-Z0-9_]+)( ?)(=)( ?)((-?)[0-9_]+)(;)") } };

StringParser::StringParser(std::string t) : text(t), pinList("")
{
	assert(t.size() != 0);
	pinList = this->createPinList(this->text);
	text = this->removeComments(this->text);
}

std::string StringParser::createPinList( std::string t )
{
	size_t it = t.find("/**");
	if ( it == std::string::npos )
	{
		return "";
	}
	size_t aux = t.find("**/");
	t = t.substr(it+4,aux-it-4);
	return t;
}

std::string StringParser::removeComments( std::string t )
{
	size_t it = 0;
	//Remove one line comments
	while (  ( it = t.find("//",it ) ) != std::string::npos )
	{
		size_t aux = t.find("\n",it);
		if ( aux == std::string::npos )
		{
			t = t.substr(0,it);
			continue;
		}
		t = t.substr(0,it) + t.substr(aux+1,std::string::npos);
	}
	//Remove /* */ comments
	it = 0 ;
	while ( (  it = t.find("/*",it) ) != std::string::npos )
	{
		size_t aux = t.find("*/",it);
		t = t.substr(0,it) + t.substr(aux+2, std::string::npos);
	}
	return t;
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
		size_t pos_space = matchString.find(" ");
		matchString = matchString.substr(pos_space+1,std::string::npos);
		matchString = matchString.substr(0,matchString.find(";"));
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
		size_t pos_space = matchString.find(" ");
		matchString = matchString.substr(pos_space+1,std::string::npos);
		matchString = matchString.substr(0,matchString.find(";"));
		rez.push_back( Chan(matchString) );
	}
	return rez;
}

std::map<std::string,std::string> StringParser::generateSystems()
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

std::vector<std::pair<std::string,int> > StringParser::generateSymbols()
{
	std::vector<std::pair<std::string,int> > rez;
	auto words_begin = std::sregex_iterator(text.begin(), text.end(), regex["declVar"] );
	auto words_end = std::sregex_iterator();

	for ( std::sregex_iterator i = words_begin; i != words_end; ++i )
	{
		std::string matchString = i->str();
		auto poz = matchString.find_last_of(" ");
		std::string name = matchString.substr( poz + 1, std::string::npos );
		poz = name.find( ";" );
		name = name.substr( 0, poz );
		rez.push_back(std::pair<std::string,int>(name,0));
	}

	words_begin = std::sregex_iterator(text.begin(), text.end(), regex["defVar"] );
	for( std::sregex_iterator i = words_begin; i != words_end; ++i )
	{
		std::string matchString = i->str();
		auto poz = matchString.find(" ");
		matchString = matchString.substr( poz + 1, std::string::npos );
		std::string name = matchString.substr(0, matchString.find(" ") );
		std::string value = matchString.substr( matchString.find_last_of(" ") + 1, std::string::npos );
		value = value.substr(0, value.find(";") );
		rez.push_back(std::pair<std::string,int>(name,std::stoi(value)));
	}
	return rez;
}

std::vector<Pin> StringParser::generatePins()
{
	std::vector<Pin> rez;
	if ( pinList == "" )
	{
		return rez;
	}
	std::vector<std::string> lines = splitString(pinList,"\n");
	for ( auto l : lines )
	{
		if ( l == "" )
		{
			continue;
		}
		std::vector<std::string> infos = splitString(l," " );
		if ( ( infos[2] != "OUT" ) && ( infos[2] != "IN" ) )
		{
			assert(!"Incorrect pin status");
		}
		rez.push_back( Pin( infos[1], infos[2], std::stoi( infos[3] ) ) );
	}
	return rez;
}