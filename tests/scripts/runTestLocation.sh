#!/bin/bash

g++-4.9 -std=c++11 ../tests/testLocation.cpp ../components/location.a
./a.out
if [ $? == 0 ]; then
	echo "Passed testLocation"
	rm a.out
else
	echo "Failed testLocation"
	rm a.out
fi