#ifndef _FSM_H_
#define _FSM_H_

#include <vector>
#include <map>
#include <memory>

#include "template.h"

class TimedAutomata
{
public:
	TimedAutomata() {}
	
	void step();

	void addTemplate(const Template& m );
	void addSystems(const std::map<std::string,std::string> systemsName);

private:
	std::vector<Template> templates;
	std::vector<Template> systems;
};

#endif