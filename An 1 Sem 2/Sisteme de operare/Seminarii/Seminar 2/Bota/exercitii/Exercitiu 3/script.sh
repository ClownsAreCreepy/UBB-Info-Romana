#!/bin/bash

fisiere=$(ls -l | grep '\.txt' | awk '{print $9}')

if [ -z "$fisiere" ]; then
	echo "Nu exista fisier de tip text in director!"
	exit 1
fi

for file in $fisiere 
do
	echo ""
	echo "Fisierul $file: "
	if [ ! -s $file ]
	then
		echo "Fisierul e gol!"
	elif [ $(cat $file | wc -l) -lt 10 ]
	then
		echo "$(cat $file)"
	else
		echo "$(head -n 5 $file)"
		echo "$(tail -n 5 $file)"
	fi	
done
