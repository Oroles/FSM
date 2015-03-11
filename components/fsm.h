#ifndef _FSM_H_
#define _FSM_H_

#include <vector>
#include <memory>

#include "module.h"
#include "../utils/utils.h"
#include "./variables/clock.h"
#include "./variables/chan.h"

class FSM
{
public:
	FSM() {}
	
	void step();
	void startModules();

	void addModule(const Module& m )
	{
		modules.push_back( m );
	}
	void addChannels(const std::vector<Chan>& c)
	{
		display(DebugMessagePriority::Priority::Level1, "There were added ", c.size(), "channels to FSM\n" );
		channels = c;
	}
	void addClocks(const std::vector<Clock>& c)
	{
		display(DebugMessagePriority::Priority::Level1, "There were added ", c.size(), "clocks to FSM\n" );
		clocks = c;
	}
private:
	std::vector<Module> modules;
	std::vector<Chan> channels;
	std::vector<Clock> clocks;
};

#endif