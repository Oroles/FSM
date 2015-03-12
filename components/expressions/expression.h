#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>
#include <iostream>

class Expression
{
public:
	Expression();
	Expression(std::string ex);
	Expression(const Expression& rhs);
	Expression& operator=(const Expression& rhs);
	bool operator==(const Expression& rhs);
	bool evaluate();
	std::string getFirst() const;
	std::string getOp() const;
	std::string getSecond() const;

private:
	friend std::ostream& operator<<(std::ostream&, const Expression&);
	int get_value(std::string);

	std::string first;
	std::string op;
	std::string second;
};

#endif