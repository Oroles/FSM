#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>
#include <iostream>
#include <algorithm>

class Expression
{
public:
	Expression();
	Expression(std::string ex);
	Expression(const Expression& rhs);
	Expression(Expression&& rhs);
	Expression& operator=(const Expression& rhs);
	bool operator==(const Expression& rhs);
	bool evaluate() const;
	std::string getFirst() const;
	std::string getOp() const;
	std::string getSecond() const;

private:
	enum class OperandType { TypeClock, TypeSymbol, TypeValue, TypeUnknown };
	friend std::ostream& operator<<(std::ostream&, const Expression&);
	int get_value(std::string, OperandType) const;
	void set_value(std::string, OperandType, int) const;
	OperandType findType( std::string name);

	std::string first;
	std::string op;
	std::string second;
	OperandType firstOperand = OperandType::TypeUnknown;
	OperandType secondOperand = OperandType::TypeUnknown;
};

#endif