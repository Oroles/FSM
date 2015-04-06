#!/bin/bash

g++-4.9 -std=c++11 ../tests/testState.cpp ../components/state.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testState"
	rm a.out
else
	echo "Failed testState"
	rm a.out
fi