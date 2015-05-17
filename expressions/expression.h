#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

class Expression
{
public:
	Expression();
	Expression(std::string ex);
	Expression(const Expression& rhs);
	Expression(Expression&& rhs);
	const Expression& operator=(const Expression& rhs);
	bool operator==(const Expression& rhs);
	int evaluate() const;
	bool isValidGuard() const;
	bool isValidUpdate() const;
	bool isValidInvariant() const;

	void setSystemName(const std::string name);

private:

	friend std::ostream& operator<<(std::ostream&, const Expression&);
	int get_value(std::string) const;
	void set_value(std::string, int) const;
	std::vector<std::string> generateRPN();

	std::string expression;
	std::vector<std::string> rpn;
	std::string systemName;
};

#endif