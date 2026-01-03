#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage: $0 <folder>"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "Parametrul trebuie sa existe si sa fie un director!"
	exit 2
fi

find $1 -type f | 
	while read -r fila
	do
		if [ $(basename "$fila" | wc -m) -lt 20 ]
		then
			echo "$fila"
			if file "$fila" | grep -q 'text'; then
				head "$fila"
			fi
			echo ""
		fi
	done
