#!/bin/bash

g++-4.9 -std=c++11 -pthread ../tests/testExpression.cpp ../expressions/expression.a \
				../tables/symboltable.a ../tables/clocktable.a ../variables/clock.a ../utils/utils.a \
				../tables/localtable.a ../tables/pintable.a ../variables/pin.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testExpression"
	rm a.out
else
	echo "Failed testExpression"
	rm a.out
fi