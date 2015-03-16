#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <cassert>
#include <memory>
#include <map>
#include <vector>

#include "../variables/clock.h"
#include "../variables/chan.h"
#include "../components/module.h"

class StringParser
{
public:
	StringParser( std::string t );
	std::vector<Clock> generateClocks();
	std::vector<Chan> generateChannels();
	std::vector<Module> generateModules();

private:

	std::string text;
};

#endif