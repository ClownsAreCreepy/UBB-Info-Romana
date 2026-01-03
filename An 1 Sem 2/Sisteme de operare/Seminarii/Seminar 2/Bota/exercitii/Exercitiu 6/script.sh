#!/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage: $0 <director>"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "Fisierul obtinut trebuie sa existe si sa fie un director!"
	exit 2
fi

find "$1" -type f -perm -222 | 
	while read -r fila
	do
		mv "$fila" "$fila.txt"
	done
