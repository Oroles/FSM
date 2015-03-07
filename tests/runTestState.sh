#!/bin/bash

g++ -std=c++11 -pthread testState.cpp
./a.out
if [ $? == 0 ]; then
	echo "Passed testState"
	rm a.out
else
	echo "Failed testState"
	rm a.out
fi