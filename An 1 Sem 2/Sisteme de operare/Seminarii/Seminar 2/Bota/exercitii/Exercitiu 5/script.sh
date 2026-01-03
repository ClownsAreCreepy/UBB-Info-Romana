#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage: $0 <directory>"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "Fisierul trebuie sa existe si sa fie director!"
	exit 2
fi

fisiere=$(find $1 -maxdepth 1 -type f)

nr_fisiere=0
nr_linii=0

for fila in $fisiere
do
	if file "$fila" | grep -q 'text'
	then
		nr_linii=$((nr_linii + $(wc -l < "$fila")))
		nr_fisiere=$((nr_fisiere + 1))
	fi
done

if [ "$nr_fisiere" -eq 0 ]
then
	echo "Directorul $1 nu are fisiere .txt"
	exit 3
fi

avg=$(echo "scale=2; $nr_linii/$nr_fisiere" | bc)
echo Media: $avg
