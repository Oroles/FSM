#!/bin/bash

g++ -std=c++11 -pthread ../tests/testExpression.cpp ../expressions/expression.a ../components/symboltable.a ../utils/utils.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testExpression"
	rm a.out
else
	echo "Failed testExpression"
	rm a.out
fi