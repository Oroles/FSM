#include "expression.h"

#include "../utils/utils.h"
#include "../tables/symboltable.h"
#include "../tables/clocktable.h"

#include <vector>
#include <cassert>
#include <sstream>

#define EXECUTE_BLOCK( s ){  std::string first = aux[ aux.size() - 1 ]; \
						   std::string second = aux[ aux.size() - 2 ];\
						   aux.erase( aux.end() - 2, aux.end() );\
						   std::string rez = std::to_string( get_value(second) s get_value(first) );\
						   aux.push_back( rez );\
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
													std::pair<std::string,int>("-",3),
													std::pair<std::string,int>("*",4),
													std::pair<std::string,int>("/",4) }; 

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

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

Expression::Expression()
{

}

Expression::Expression(std::string ex) : expression(ex)
{
	assert(ex.size() != 0 );
	for ( auto& o : operators )
	{
		replaceString( expression, o.first, std::string( " " + o.first + " " ) );
	}
	std::cout << expression << std::endl;
	rpn = this->generateRPN();
}

Expression::Expression(const Expression& rhs) : expression( rhs.expression ), rpn( rhs.rpn )
{

}

Expression::Expression(Expression&& rhs) : expression( std::move( rhs.expression ) ), rpn( std::move(rhs.rpn) )
{

}

Expression& Expression::operator=(const Expression& rhs)
{
	rpn = rhs.rpn;
	expression = rhs.expression;
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
				if ( t == "*" ) EXECUTE_BLOCK(*);
				if ( t == ">")  EXECUTE_BLOCK(>);
				if ( t == "<" ) EXECUTE_BLOCK(<);
				if ( t == "-" ) EXECUTE_BLOCK(-);
				if ( t == "/" ) EXECUTE_BLOCK(/);
				if ( t == ">=" ) EXECUTE_BLOCK(>=);
				if ( t == "<=" ) EXECUTE_BLOCK(<=);
				if ( t == "==" ) EXECUTE_BLOCK(==);
				if ( t == "!=" ) EXECUTE_BLOCK(!=);
				if ( t == "=" ) {
					std::string first = aux[ aux.size() - 1 ];
				   	std::string second = aux[ aux.size() - 2 ];
					aux.erase( aux.end() - 2, aux.end() );
				   	set_value( second, get_value(first) );
				   	aux.push_back( "1" );
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
	display(DebugMessagePriority::Expression, "Expression: ", expression, " is evaluated to ", aux[0], "\n" );
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
	assert(!"Should not reach here");
	return 0;
}

void Expression::set_value(std::string name, int val) const
{
	if ( SymbolTable::getInstance().exists(name) )
	{
		SymbolTable::getInstance().setValue(name,val);
		return;
	}
	if ( ClockTable::getInstance().exists(name) )
	{
		ClockTable::getInstance().setValue(name,val);
		return;
	}
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

std::ostream& operator<<(std::ostream& o, const Expression& e)
{
	o << "Expression: " << e.expression << std::endl;
	return o;
}