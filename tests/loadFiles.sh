#!/bin/bash

cd ..
files=( $(ls | grep ".xml" ) )

for file in "${files[@]}"
do
	echo -n "Test file "
	echo "$file"
	./demoproject -d 0 -i "$file" -quit
done

#rm ./demoproject

echo "Done"
