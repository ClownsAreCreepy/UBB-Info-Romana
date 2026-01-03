#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <directory>"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Fisierul trebuie sa existe si sa fie director!"
	exit 2
fi

fisiere=$(find $1 -maxdepth 1 -type f)

for fila in $fisiere
do
	nr_cifre=$(grep -E '\b[0-9]{5,}\b' $fila | wc -l)
	if [ $nr_cifre -ne 0 ]
	then
		echo "$(echo "$fila" | awk -F/ '{print $NF}')"
	fi
done

