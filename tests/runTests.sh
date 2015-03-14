#!/bin/bash

# !Important! - how to create tests
# 1. if there are no files in /tests/components or other folders first run the scrip generateLibs.sh
# 1a. if there are files continue with the next step
# 2. create a separate cpp file (eg. testState.cpp ) for each class ( State ) you want to test
# 3. write the tests for the class by looking at the interface( state.h ). Try to cover as many as possible cases
# 4. create a script that will compile the file ( eg. runTestState.sh )
# 5. in that file is possible to add extra libs for the compiler ( eg. ./components/state.a )
# 6. run the script and check if all the tests failed
# 7. if you want to delete .h and .a file run make clean in tests folder

for file in ./*.sh
do
	if [[ "$file" != "./createTests.sh" && "$file" != "./runTests.sh" ]]
	then
		bash "$file"
	fi
done