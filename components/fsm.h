#ifndef _FSM_H_
#define _FSM_H_

#include <vector>
#include <map>
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

	void addTemplate(const Module& m );
	void addChannels(const std::vector<Chan>& c);
	void addClocks(const std::vector<Clock>& c);
	void addModules(const std::map<std::string,std::string> modulesName);

private:
	std::vector<Module> templates;
	std::vector<Module> modules;
	std::vector<Chan> channels;
	std::vector<Clock> clocks;
};

#endif