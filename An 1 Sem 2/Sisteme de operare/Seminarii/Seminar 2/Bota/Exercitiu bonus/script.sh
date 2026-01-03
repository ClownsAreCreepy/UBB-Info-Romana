#!/bin/bash
# Se da ca argument un director, in director se cauta fisiere .c care au prima linie std::cout
#si sa se afiseze aceste fisiere

if [ $# -ne 1 ]
then
	echo "Usage: $0 <folder>"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "Parameter must exist and must be a folder!"
	exit 2
fi

find $1 -type f -name "*.c" | 
	while read -r file
	do
		if sed -n '1p' $file | grep -Eq 'std::cout'; then
			echo $file
		fi
	done
