#ifndef _STRING_PARSER_H_
#define _STRING_PARSER_H_

#include <string>
#include <cassert>
#include <memory>

#include "../components/variables/variable.h"

class StringParser
{
public:
	StringParser( std::string t ) : text(t)
	{
		assert(t.size() != 0);
	}
	std::shared_ptr<Variable> nextVariable();

private:
	std::string text;
};

#endif