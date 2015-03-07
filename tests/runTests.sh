#!/bin/bash

for file in ./*.sh
do
	if [[ "$file" != "./createTests.sh" && "$file" != "./runTests.sh" ]]
	then
		bash "$file"
	fi
done