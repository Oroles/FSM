#!/bin/bash

g++ -std=c++11 -pthread ../tests/testState.cpp ../components/state.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testState"
	rm a.out
else
	echo "Failed testState"
	rm a.out
fi