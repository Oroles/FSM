#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <cassert>
#include <memory>
#include <map>
#include <vector>

#include "../variables/clock.h"
#include "../variables/chan.h"

class StringParser
{
public:
	StringParser( std::string t );
	std::vector<Clock> generateClocks();
	std::vector<Chan> generateChannels();
	std::map<std::string,std::string> generateModules();

private:
	std::string removeComments( std::string );
	std::string text;
};

#endif