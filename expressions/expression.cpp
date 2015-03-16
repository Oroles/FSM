#include "expression.h"

#include "../utils/utils.h"
#include "../components/symboltable.h"

#include <vector>
#include <cassert>

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

Expression::Expression()
{

}

Expression::Expression(std::string ex)
{
	assert(ex.size() != 0 );
	std::size_t pos;
	std::vector<std::string> operands;
	while ( ( pos = ex.find(" ") ) != std::string::npos )
	{
		std::string aux = ex.substr(0,pos);
		operands.push_back( aux );
		ex = ex.substr(pos+1);
	}
	first = operands[0];
	op = operands[1];
	second = ex;
}

Expression::Expression(const Expression& rhs) : first(rhs.first), op(rhs.op), second(rhs.second)
{
	assert( first != "" );
	assert( op != "" );
	assert( second != "" );
}

Expression& Expression::operator=(const Expression& rhs)
{
	first = rhs.first;
	op = rhs.op;
	second = rhs.second;
	assert( first != "" );
	assert( op != "" );
	assert( second != "" );
	return *this;
}

bool Expression::operator==(const Expression& rhs)
{
	return first==rhs.first && op==rhs.op && second==rhs.second;
}

bool Expression::evaluate() const
{
	display(DebugMessagePriority::Expression, "Is evaluated ", *this );
	switch( str2int(op.c_str()) )
	{
		case str2int(">=") :
			{
				return get_value(first) >= get_value(second);
			}
		case str2int(">") :
			{
				return get_value(first) > get_value(second);
			}
		case str2int("<") :
			{
				return get_value(first) < get_value(second);
			}
		case str2int("<=") :
			{
				return get_value(first) <= get_value(second);
			}
		default:
			return false;
	}
	return false;
}

int Expression::get_value(std::string name) const
{
	if ( is_integer( name ) ) //The name contains only digits
	{
		return std::stoi(name); //Convert to digits
	}
	else
	{
		int value = SymbolTable::getInstance().getEntry(name);
		return value;
	}
	return 0;
}

std::string Expression::getFirst() const
{
	return first;
}

std::string Expression::getOp() const
{
	return op;
}

std::string Expression::getSecond() const
{
	return second;
}

std::ostream& operator<<(std::ostream& o, const Expression& e)
{
	o << "Expression: " << e.getFirst() << " " << e.getOp() << " " << e.getSecond() << "\n";
	return o;
}