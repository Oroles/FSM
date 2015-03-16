#!/bin/bash

g++ -std=c++11 -pthread ../tests/testExpression.cpp ../expressions/expression.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testExpression"
	rm a.out
else
	echo "Failed testExpression"
	rm a.out
fi