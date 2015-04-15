#!/bin/bash

g++-4.9 -std=c++11 ../tests/testTemplate.cpp  ../components/template.a ../components/transition.a ../expressions/expression.a \
				../expressions/sync.a ../components/state.a ../tables/pintable.a ../tables/symboltable.a \
				../tables/localtable.a ../tables/clocktable.a  ../tables/chantable.a ../variables/chan.a \
				../variables/clock.a ../variables/pin.a ../utils/utils.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testTemplate"
	rm a.out
else
	echo "Failed testTemplate"
	rm a.out
fi