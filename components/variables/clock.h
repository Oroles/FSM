#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "variable.h"

class Clock : public Variable
{
public:
	Clock( std::string n, int val = 0) : Variable(n), value(val)
	{

	}

	void set(int value) override;
	int get() override;

	~Clock();
private:
	int value = 0;
};

#endif