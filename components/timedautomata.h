#ifndef _FSM_H_
#define _FSM_H_

#include <vector>
#include <map>
#include <memory>

#include "module.h"

class TimedAutomata
{
public:
	TimedAutomata() {}
	
	void step();

	void addTemplate(const Module& m );
	void addModules(const std::map<std::string,std::string> modulesName);

private:
	std::vector<Module> templates;
	std::vector<Module> modules;
};

#endif