#ifndef _CHAN_H_
#define _CHAN_H_

#include "variable.h"

class Chan : public Variable
{
public:
	Chan( std::string name, int val = 0 ) : Variable(name), value(val)
	{

	}

	void set(int value) override;
	int get() override;

	~Chan();

private:
	int value = 0;
};

#endif