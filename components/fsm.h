#ifndef _FSM_H_
#define _FSM_H_

#include <vector>
#include <memory>

#include "module.h"
#include "variables/variable.h"

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
private:
	std::vector<Module> modules;
	std::vector<std::shared_ptr<Variable>> variables;
};

#endif