#include "expression.h"

#include "../utils/utils.h"
#include "../components/symboltable.h"

#include <vector>
#include <cassert>

const std::vector<std::pair<std::string,int>> operators { std::pair<std::string,int>( "<=", 2 ),
														  std::pair<std::string,int>( ">=", 2 ),
														  std::pair<std::string,int>( ":=", 2),
														  std::pair<std::string,int>( "<", 1 ),
														  std::pair<std::string,int>( ">", 1 ),
														  std::pair<std::string,int>( "=", 1 ) };

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

	ex.erase(std::remove_if(ex.begin(),ex.end(),isspace),ex.end());
	auto found = std::find_if( operators.begin(), operators.end(), [&ex](std::pair<std::string,int> o ) -> bool { return (ex.find(o.first) != std::string::npos ); } );
	
	if ( found != operators.end() )
	{
		std::size_t pos = ex.find(found->first);
		first = ex.substr(0,pos);
		op = ex.substr(pos,found->second);
		second = ex.substr(pos+found->second,std::string::npos);
	}
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
		case str2int(":=") :
		case str2int("=") :
			{
				int secondValue = get_value(second);
				SymbolTable::getInstance().updateEntry(first,secondValue);
				return true;
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