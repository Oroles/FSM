#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "transition.h"

class Template;

class Observer
{
public:
	void addObservable(Template* rhs);
	bool isAvailable(const Template& temp, const Transition& trans, const std::string channelName );

private:
	struct Data
	{
		Template* temp;
		std::shared_ptr<Transition> trans;
		std::string name;
	};

	std::vector<Data> senders;
	std::vector<Data> receivers;
};

#endif