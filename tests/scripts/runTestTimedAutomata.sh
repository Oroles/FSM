#!/bin/bash

g++-4.9 -std=c++11 ../tests/testTimedAutomata.cpp  ../components/timedautomata.a ../components/template.a ../components/edge.a ../expressions/expression.a \
				../components/location.a ../tables/pintable.a ../tables/symboltable.a \
				../tables/localtable.a ../tables/clocktable.a  ../tables/chantable.a ../variables/chan.a \
				../variables/clock.a ../variables/pin.a ../utils/utils.a ../components/observer.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testTimedAutomata"
	rm a.out
else
	echo "Failed testTimedAutomata"
	rm a.out
fi
