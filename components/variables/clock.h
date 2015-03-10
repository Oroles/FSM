#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "variable.h"

class Clock : public Variable
{
public:
	Clock( std::string n, int val = 0) : Variable(n), value(val)
	{
		assert(val >= 0 );
	}

	Clock(const Clock& rhs);
	Clock& operator=(const Clock& rhs);
	bool operator==(const Clock& rhs);

	void set(int value) override;
	int get() override;

	~Clock();
private:
	int value = 0;
};

#endif