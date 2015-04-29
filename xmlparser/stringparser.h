#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <cassert>
#include <memory>
#include <map>
#include <vector>

#include "../variables/clock.h"
#include "../variables/chan.h"
#include "../variables/pin.h"
#include "../utils/plaindata.h"

class StringParser
{
public:
	StringParser( std::string t );
	std::vector<Clock> generateClocks();
	std::vector<Chan> generateChannels();
	std::vector<PlainData> generateSymbols();
	std::map<std::string,std::string> generateSystems();
	std::vector<Pin> generatePins();

private:
	std::string removeComments( std::string );
	std::string createPinList( std::string );
	std::string text;
	std::string pinList;
};

#endif