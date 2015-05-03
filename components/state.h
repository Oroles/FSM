#ifndef _STATE_H_
#define _STATE_H_

#include <string>
#include <iostream>
#include <cassert>

class State
{
public:
	State();
	State(const std::string n);
	State(const State& rhs);
	State(State&& rhs);

	const State& operator=(const State& rhs);
	bool operator==(const State& rhs) const;
	bool operator!=(const State& rhs) const;

	friend std::ostream& operator<<(std::ostream& o, const State& rhs);

	std::string getName() const;
	void setName(std::string n);

private:
	std::string name;
};

#endif