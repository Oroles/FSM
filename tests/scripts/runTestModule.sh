#!/bin/bash

g++-4.9 -std=c++11 ../tests/testModule.cpp  ../components/module.a ../components/tranzition.a ../expressions/expression.a \
				../expressions/sync.a ../components/state.a ../tables/pintable.a ../tables/symboltable.a \
				../tables/localtable.a ../tables/clocktable.a  ../tables/chantable.a ../variables/chan.a \
				../variables/clock.a ../variables/pin.a ../utils/utils.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testModule"
	rm a.out
else
	echo "Failed testModule"
	rm a.out
fi