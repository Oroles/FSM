#include "expression.cpp"

#include "../../utils/utils.h"

#include <vector>
#include <cassert>

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

Expression::Expression(std::string ex)
{
	assert(ex.size() != 0 );
	std::size_t pos;
	std::vector<std::string> operands;
	while ( ( pos = ex.find(" ") != std::string::npos )
	{
		operands.push_back( ex.substr(0,pos) );
		ex = ex.substr(pos+1);
	}
	first = operands[0];
	op = operands[1];
	second = operands[2];
}

Expression(const Expression& rhs) : first(rhs.first), op(rhs.op), second(rhs.second)
{
	assert( first != "" );
	assert( op != "" );
	assert( second != "" );
}

Expression& operator=(const Expression& rhs) : first(rhs.first), op(rhs.op), second(rhs.second)
{
	assert( first != "" );
	assert( op != "" );
	assert( second != "" );
}

bool operator==(const Expression& rhs)
{
	return first==rhs.first && op==rhs.op && second==rhs.second;
}

bool Expression::evaluate()
{
	switch( str2int(op) )
	{
		case str2int(">=")
			{
				return get_value(first) >= get_value(second);
			}
		case str2int(">")
			{
				return get_value(first) > get_value(second);
			}
	}
	return true;
}

int Expression::get_value(std::string name)
{
	if ( is_integer( name ) ) //The name contains only digits
	{
		return std::stoi(name); //Convert to digits
	}
	else
	{
		//Has to go to the FSM to get the value of name
	}
}