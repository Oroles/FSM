#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>

class Expression
{
public:
	Expression(std::string ex);
	Expression(const Expression& rhs);
	Expression& operator=(const Expression& rhs);
	bool operator==(const Expression& rhs);
	bool evaluate();

private:
	int get_value(std::string);
	std::string first;
	std::string op;
	std::string second;
};

#endif