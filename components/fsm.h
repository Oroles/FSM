#ifndef _FSM_H_
#define _FSM_H_

#include <vector>

#include "module.h"

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
private:
	std::vector<Module> modules;
};

#endif