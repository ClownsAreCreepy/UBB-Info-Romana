#!/bin/bash

# Verificam sa avem un singur argument
if [ $# -ne 1 ]
then
	echo "Usage: $0 <argument>"
	exit 1
fi

# Verificam ca argumentul dat sa fie un director
if ! [ -d "$1" ]
then
	echo "Argument must be a directory!"
	exit 2
fi

# Verificam ficare fisier din director
find "$1" -type f | while read -r file
	do
		# Sed pentru a gasi numere cu mai mult de 5 cifre
		# Grep pentru a verifica daca exista si pentru a returna in if
		# Basename pentru a lua doar numele fisierului, fara calea la el
		if sed -n '/[0-9]\{6,\}/p' "$file" | grep -q "."
		then
			echo "$(basename "$file")"
		fi
	done
