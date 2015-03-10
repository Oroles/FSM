#ifndef _FSM_H_
#define _FSM_H_

#include <vector>
#include <memory>

#include "module.h"
#include "variables/variable.h"
#include "../utils/utils.h"

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
	void addVariable(const std::shared_ptr<Variable> v )
	{
		variables.push_back( v );
	}
	void setVariables(const std::vector<std::shared_ptr<Variable>>&& v )
	{
		display(DebugMessagePriority::Priority::Level1, "Set ", v.size(), "variables to fsm.\n");
		variables.clear();
		variables = v;
	}
private:
	std::vector<Module> modules;
	std::vector<std::shared_ptr<Variable>> variables;
};

#endif