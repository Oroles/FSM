#!/bin/bash

g++-4.9 -std=c++11 ../tests/testTimedAutomata.cpp  ../components/timedautomata.a ../components/template.a ../components/transition.a ../expressions/expression.a \
				../expressions/sync.a ../components/state.a ../tables/pintable.a ../tables/symboltable.a \
				../tables/localtable.a ../tables/clocktable.a  ../tables/chantable.a ../variables/chan.a \
				../variables/clock.a ../variables/pin.a ../utils/utils.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testFsm"
	rm a.out
else
	echo "Failed testFsm"
	rm a.out
fi