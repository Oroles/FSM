#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <string>
#include <cassert>

class Variable
{
public:
	Variable() : name("")
	{
	}

	Variable( std::string n )
	{
		assert(n.size()!=0);
		name = n;
	}
	Variable( const Variable& rhs)
	{
		assert(rhs.name.size()!=0);
		name = rhs.name;
	}

	Variable& operator=(const Variable& rhs)
	{
		assert(rhs.name.size()!=0);
		name = rhs.name;
		return *this;
	}

	bool operator==(const Variable& rhs)
	{
		return this->name == rhs.name;
	}

	virtual void set( int value ) = 0;
	virtual int get() = 0;

	virtual void setName( std::string n )
	{
		assert(n.size() != 0);
		name = n;
	}
	virtual std::string getName() const
	{
		return name;
	}

	virtual ~Variable() {}
protected:
	std::string name;
};

#endif