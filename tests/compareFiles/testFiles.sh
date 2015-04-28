#!/bin/bash

cp ../../demoproject ./
cp ../../xmlFiles/*.xml ./

for file in *.xml
do
	./demoproject -d 63 -i $file -step < input.txt > tmprez.txt
	diff tmprez.txt ./results/result${file} | grep -v ^@ | wc -l > countDiffFile
	read -r differences < countDiffFile
	if [ $differences -ne 0 ]
	then
		echo -n "FAILED: "
		echo $file
	else
		echo -n "PASS: "
		echo $file
	fi
	rm countDiffFile
	rm tmprez.txt
done

rm ./demoproject
rm ./*.xml
