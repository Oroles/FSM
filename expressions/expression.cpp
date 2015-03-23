#include "expression.h"

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/clocktable.h"

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
	firstOperand = this->findType( first );
	secondOperand = this->findType( second );
}

Expression::Expression(const Expression& rhs) : first(rhs.first), op(rhs.op), second(rhs.second), firstOperand(rhs.firstOperand), secondOperand(rhs.secondOperand)
{
	assert( first != "" );
	assert( op != "" );
	assert( second != "" );
}

Expression::Expression(Expression&& rhs) : first(std::move(rhs.first)), op(std::move(rhs.op)), second(std::move(rhs.second)),
											firstOperand(std::move(rhs.firstOperand)), secondOperand(std::move(rhs.secondOperand))
{

}

Expression& Expression::operator=(const Expression& rhs)
{
	first = rhs.first;
	op = rhs.op;
	second = rhs.second;
	firstOperand = rhs.firstOperand;
	secondOperand = rhs.secondOperand;
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
	display(DebugMessagePriority::Expression, "Is evaluated ", *this, "\n" );
	switch( str2int(op.c_str()) )
	{
		case str2int(">=") :
			{
				return get_value(first,firstOperand) >= get_value(second,secondOperand);
			}
		case str2int(">") :
			{
				return get_value(first,firstOperand) > get_value(second,secondOperand);
			}
		case str2int("<") :
			{
				return get_value(first,firstOperand) < get_value(second,secondOperand);
			}
		case str2int("<=") :
			{
				return get_value(first,firstOperand) <= get_value(second,secondOperand);
			}
		case str2int(":=") :
		case str2int("=") :
			{
				int secondValue = get_value(second,secondOperand);
				this->set_value(first,firstOperand,secondValue);
				return true;
			}
		default:
			return false;
	}
	return false;
}

int Expression::get_value(std::string name, Expression::OperandType type) const
{
	if ( is_integer( name ) ) //The name contains only digits
	{
		return std::stoi(name); //Convert to digits
	}
	else
	{
		int value = 0;
		switch( type )
		{
			case OperandType::TypeSymbol: value = SymbolTable::getInstance().getValue(name); break;	
			case OperandType::TypeClock: value = ClockTable::getInstance().getValue(name); break;
			case OperandType::TypeUnknown:
			default: break;
		}
		return value;
	}
	return 0;
}

void Expression::set_value(std::string name, Expression::OperandType type, int val) const
{
	switch( type )
		{
			case OperandType::TypeSymbol: SymbolTable::getInstance().setValue(name,val); break;	
			case OperandType::TypeClock: ClockTable::getInstance().setValue(name,val); break;
			case OperandType::TypeUnknown:
			default: break;
		}
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

Expression::OperandType Expression::findType(std::string name)
{
	if ( SymbolTable::getInstance().exists(name) )
	{
		return OperandType::TypeSymbol;
	}
	if ( ClockTable::getInstance().exists(name) )
	{
		return OperandType::TypeClock;
	}
	return OperandType::TypeUnknown;
}

std::ostream& operator<<(std::ostream& o, const Expression& e)
{
	o << "Expression: " << e.getFirst() << " " << e.getOp() << " " << e.getSecond();
	return o;
}