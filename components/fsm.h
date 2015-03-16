#ifndef _FSM_H_
#define _FSM_H_

#include <vector>
#include <memory>

#include "module.h"
#include "../variables/clock.h"
#include "../variables/chan.h"

class FSM
{
public:
	FSM() {}
	
	void step();
	void startModules();

	void addModule(const Module& m );
	void addChannels(const std::vector<Chan>& c);
	void addClocks(const std::vector<Clock>& c);

private:
	std::vector<Module> modules;
	std::vector<Chan> channels;
	std::vector<Clock> clocks;
};

#endif