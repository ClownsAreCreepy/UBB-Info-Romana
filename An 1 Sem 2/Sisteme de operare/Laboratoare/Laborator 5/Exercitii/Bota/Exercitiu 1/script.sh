#!/bin/bash

# Verificam sa existe un singur argument
if [ $# -ne 1 ]
then
	echo "Usage: $0 <argument>"
	exit 1
fi

# Verificam ca argumentul sa fie un numar:
# Varianta 1:
if ! [[ "$1" =~ ^[0-9]+$ ]]
then
	echo "Argument must be a number!"
	exit 2
fi

# Varianta 2:
# Functioneaza pe ideea n1 -eq n2 is true only if n1 and n2 are integers and are equal
if ! [ "$1" -eq "$1" ]
then
	echo "Argument must be a number!"
	exit 2
fi

for (( i = 1; i <= "$1"; ++i ))
do
	touch file_$i.txt
	sed -n "$i,$((i + 5))p" passwd.fake > file_$i.txt 
done
