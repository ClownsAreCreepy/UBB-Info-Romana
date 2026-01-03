#!/bin/bash

if (( $# % 3 != 0 || $# == 0 ))
then
	echo "Parametrii trebuie sa fie triplete !"
	exit 1
fi

while [ $# -ne 0 ]
do
	nume_fisier="$1"
	cuvant="$2"
	k="$3"

	echo fisier: $nume_fisier, cuvant: $cuvant, k: $k

	if [ ! -f $nume_fisier ]
	then
		echo "Fisierul nu exista!"
	else
		awk -v word="$cuvant" -v k="$k" '{
			count = gsub (word, "&")
			if (count == k) print
		}' "$nume_fisier"
	fi

	echo ""
	shift 3
done
