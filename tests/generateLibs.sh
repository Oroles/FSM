#!/bin/bash

cd ..
path=${PWD}

process_libs()
{
	cd $1
	echo $1
	destination=$path"/tests/${1##*FSM/}"
	for fileName in *.cpp
	do
		name="${fileName%.*}"
		g++ -std=c++11 -c $fileName
		ar rvs "$name.a" "$name.o"
	done

	mv *.a $destination
	cp *.h $destination
	cp *.hpp $destination

	rm *.o
}

walk_tree()
{
	for file in $(ls -rt -d -1 $1/*)
	do
		if [ -d $file ]; then
			folderName="${file##*/}"
			if [[ "$folderName" != "tests" ]]
			then
				process_libs $file
				walk_tree $file
			fi
		fi
	done
}

walk_tree $path

