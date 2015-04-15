#include "expression.h"

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/clocktable.h"
#include "../tables/localtable.h"
#include "../tables/pintable.h"

#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <regex>

#define EXECUTE_BLOCK( s ){  std::string first = aux[ aux.size() - 1 ]; \
						   std::string second = aux[ aux.size() - 2 ];\
						   aux.erase( aux.end() - 2, aux.end() );\
						   std::string rez = std::to_string( get_value(second) s get_value(first) );\
						   aux.push_back( rez );\
						   continue;\
						}

#define EXECUTE_BLOCK_SHORT( s ){ std::string first = aux[ aux.size() - 1 ];\
								std::string second = aux[ aux.size() - 2 ]; \
								aux.erase( aux.end() - 2, aux.end() );\
								set_value( second, get_value(second) s get_value(first) );\
								aux.push_back( std::to_string( get_value(second) ) );\
								continue;\
							}

std::vector<std::pair<std::string,int>> operators{  std::pair<std::string,int>(":=",1),
													std::pair<std::string,int>(">=",2),
													std::pair<std::string,int>("<=",2),
													std::pair<std::string,int>("<",2),
													std::pair<std::string,int>(">",2),
													std::pair<std::string,int>("!=",2),
													std::pair<std::string,int>("==",2),
													std::pair<std::string,int>("=",1),
													std::pair<std::string,int>("+",3),
													std::pair<std::string,int>("+=",1),
													std::pair<std::string,int>("-",3),
													std::pair<std::string,int>("-=",1),
													std::pair<std::string,int>("<<",2),
													std::pair<std::string,int>("<<=",1),
													std::pair<std::string,int>(">>",2),
													std::pair<std::string,int>(">>=",1),
													std::pair<std::string,int>("*",4),
													std::pair<std::string,int>("*=",1),
													std::pair<std::string,int>("/",4),
													std::pair<std::string,int>("/=",1),
													std::pair<std::string,int>("%",4),
													std::pair<std::string,int>("%=",1),
													std::pair<std::string,int>(")",1),
													std::pair<std::string,int>("(",1)};

bool is_sign(std::string sign)
{
	for ( auto& p :operators )
	{
		if ( p.first == sign )
		{
			return true;
		}
	}
	return false;
}

bool higher_priority(std::string first, std::string second)
{
	int firstPriority = 0;
	int secondPriority = 0;
	for ( auto& p : operators )
	{
		if ( p.first == first )
		{
			firstPriority = p.second;
		}
		if ( p.first == second )
		{
			secondPriority = p.second;
		}
	}
	return firstPriority > secondPriority;
}

bool lower_priority(std::string first, std::string second)
{
	return !higher_priority( first, second );
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void replaceString(std::string& subject, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

bool isValidSymbol(const std::string name)
{
	std::regex symbol("([a-zA-Z0-9_]+)");
	return std::regex_match( name, symbol );
}

bool isValid(const std::string expression)
{
	std::vector<std::string> operands = split(expression, ' ' );
	for ( auto& op : operands )
	{
		if ( std::find_if(operators.begin(),operators.end(), [&op](const std::pair<std::string,int> val ){ return val.first == op; } ) != operators.end() )
		{
			continue;
		}
		if ( isValidSymbol( op ) )
		{
			continue;
		}
		return false;
	}
	return true;
}

std::string trim( std::string value )
{
	value.erase( value.begin(), std::find_if_not(value.begin(),value.end(),isspace) );
	value.erase(std::find_if(value.rbegin(), value.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), value.end());
	return value;
}

Expression::Expression()
{

}

Expression::Expression(std::string ex) : expression(ex)
{
	assert(ex.size() != 0 );
	expression = trim(expression);
	if ( !isValid(expression) )
	{
		assert(!"Invalid expression: Use this for of expression 'a = a + 4' ");
	}
	rpn = this->generateRPN();
}

Expression::Expression(const Expression& rhs) : expression( rhs.expression ), rpn( rhs.rpn ), systemName( rhs.systemName )
{

}

Expression::Expression(Expression&& rhs) : expression( std::move( rhs.expression ) ), rpn( std::move(rhs.rpn) ), systemName( std::move(rhs.systemName) )
{

}

Expression& Expression::operator=(const Expression& rhs)
{
	rpn = rhs.rpn;
	expression = rhs.expression;
	systemName = rhs.systemName;
	return *this;
}

bool Expression::operator==(const Expression& rhs)
{
	return true;
}

int Expression::evaluate() const
{
	std::vector< std::string > aux;
	for ( auto t : rpn )
	{
		if ( is_integer(t) )
		{
			aux.push_back( t );
			continue;
		}
		else
		{
			if ( is_sign(t) )
			{
				if ( t == "+" ) EXECUTE_BLOCK(+);
				if ( t == "+=" ) EXECUTE_BLOCK_SHORT(+);
				if ( t == "*" ) EXECUTE_BLOCK(*);
				if ( t == "*=" ) EXECUTE_BLOCK_SHORT(*);
				if ( t == ">")  EXECUTE_BLOCK(>);
				if ( t == "<" ) EXECUTE_BLOCK(<);
				if ( t == "-" ) EXECUTE_BLOCK(-);
				if ( t == "-=" ) EXECUTE_BLOCK_SHORT(-);
				if ( t == "/" ) EXECUTE_BLOCK(/);
				if ( t == "/=" ) EXECUTE_BLOCK_SHORT(/);
				if ( t == "%" ) EXECUTE_BLOCK(%);
				if ( t == "%=" ) EXECUTE_BLOCK_SHORT(%);
				if ( t == "<<") EXECUTE_BLOCK(<<);
				if ( t == "<<=" ) EXECUTE_BLOCK_SHORT(<<);
				if ( t == ">>" ) EXECUTE_BLOCK(>>);
				if ( t == ">>=" ) EXECUTE_BLOCK_SHORT(>>);
				if ( t == ">=" ) EXECUTE_BLOCK(>=);
				if ( t == "<=" ) EXECUTE_BLOCK(<=);
				if ( t == "==" ) EXECUTE_BLOCK(==);
				if ( t == "!=" ) EXECUTE_BLOCK(!=);
				if ( ( t == "=" ) || ( t == ":=" ) ) {
					std::string first = aux[ aux.size() - 1 ];
				   	std::string second = aux[ aux.size() - 2 ];
					aux.erase( aux.end() - 2, aux.end() );
				   	set_value( second, get_value(first) );
					aux.push_back( std::to_string( get_value(second) ) );
				   	continue;
				}
			}
			else
			{
				aux.push_back( t );
				continue;
			}
		}
	}
	display(DebugMessagePriority::Expression, "Expression: ", expression, "from template ", systemName, " is evaluated to ", aux[0], "\n" );
	return std::stoi( aux[0] );
}

int Expression::get_value(std::string name) const
{
	if ( is_integer(name) )
	{
		return stoi( name );
	}
	if ( SymbolTable::getInstance().exists(name) )
	{
		return SymbolTable::getInstance().getValue(name);
	}
	if ( ClockTable::getInstance().exists(name) )
	{
		return ClockTable::getInstance().getValue(name);
	}
	if ( LocalTable::getInstance().exists( systemName, name ) )
	{
		return LocalTable::getInstance().getValue( systemName, name);
	}
	if ( PinTable::getInstance().exists( name ) )
	{
		return PinTable::getInstance().getValue( name );
	}
	assert(!"Should not reach here");
	return 0;
}

void Expression::setSystemName(const std::string name)
{
	systemName = name;
}

void Expression::set_value(std::string name, int val) const
{
	if ( SymbolTable::getInstance().exists(name) )
	{
		SymbolTable::getInstance().setValue(name,val);
		return;
	}
	if ( PinTable::getInstance().exists(name) )
	{
		PinTable::getInstance().setValue(name,val);
		return;
	}
	if ( ClockTable::getInstance().exists(name) )
	{
		ClockTable::getInstance().setValue(name,val);
		return;
	}
	if ( LocalTable::getInstance().exists( systemName, name ) )
	{
		LocalTable::getInstance().setValue( systemName, name, val );
		return;
	}
	std::cout << name << std::endl;
	assert(!"assign a value to a non-variable");
	return;
}

std::vector<std::string> Expression::generateRPN()
{
	std::vector<std::string> out;
	std::vector<std::string> op;
	std::vector<std::string> tokens = split( expression, ' ' );
	for( auto& t : tokens )
	{
		if ( is_integer(t) )
		{
			out.push_back(t);
			continue;
		}
		if ( is_sign(t) )
		{
			if ( op.size() == 0 )
			{
				op.push_back( t );
				continue;
			}
			else
			{
				if ( t == "(" )
				{
					op.push_back( t );
					continue;
				}
				if ( t == ")" )
				{
					while( op.back() != "(" )
					{
						std::string o = op[ op.size() - 1 ];
						op.pop_back();
						out.push_back( o );
					}
					op.pop_back(); //remove the parenthesis
					continue;
				}
				if ( higher_priority(t, op[op.size()-1]) )
				{
					op.push_back( t );
					continue;
				}
				else
				{
					std::string o = op[ op.size() - 1 ];
					while( lower_priority(t,o) )
					{
						op.pop_back();
						out.push_back( o );
						if ( op.size() == 0 )
						{
							break;
						}
						o = op[ op.size() - 1];
					}
					op.push_back( t );
					continue;
				}
			}
		}
		else
		{
			out.push_back( t );
		}
	}
	while ( op.size() != 0 )
	{
		std::string o = op[ op.size() - 1 ];
		op.pop_back();
		out.push_back( o );
	}
	return out;
}

bool Expression::isValidGuard()
{
	auto it = std::find_if(rpn.begin(),rpn.end(), [](const std::string val ){ return ( ( val == "=" ) || ( val == ":=" ) ||
																					 ( val == "+=" ) || ( val == "-=" ) ||
																					 ( val == "/=" ) || ( val == "*=" ) ||
																					 ( val == ">>=" ) || ( val == "<<=" ) ||
																					 ( val == "%=" ) ); } );
	if ( it != rpn.end() )
	{
		return false;
	}
	return true;
}

bool Expression::isValidUpdate()
{
	auto it = std::find_if(rpn.begin(),rpn.end(), [](const std::string val ){ return ( ( val == "=" ) || ( val == ":=" ) ||
																					 ( val == "+=" ) || ( val == "-=" ) ||
																					 ( val == "/=" ) || ( val == "*=" ) ||
																					 ( val == ">>=") || ( val == "<<=" ) ||
																					 ( val == "%=") ); } );
	if ( it != rpn.end() )
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& o, const Expression& e)
{
	o << "Expression: " << e.expression;
	return o;
}