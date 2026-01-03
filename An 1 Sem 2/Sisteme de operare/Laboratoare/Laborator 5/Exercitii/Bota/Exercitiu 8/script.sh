#!/bin/bash

# Verificam ca nr de argumente sa fie corespunzator
# Folosim (( .. )) pentru % (calcul matematic)
if (( $# % 3 != 0 )); then
	echo "Usage: $# <arg1> <arg2> <arg3> .. <argN>, N%3==0"
	exit 1
fi

# Cat timp mai avem argumente
while [[ $# -ne 0 ]]; do

	valid=1

	# Salvam datele de care avem nevoie pentru claritate
	# si verificam daca sunt valide (fisierul si numarul)
	file=$1
	if ! [[ -f "$file" ]]; then
		echo "Fisierul $file nu exista!"
		valid=0
	fi

	word=$2
	
	freq=$3
	if ! [[ "$freq" =~ ^[0-9]+$ ]]; then
		echo "Frecventa pentru fisierul $file nu e un numar natural!"
		valid=0
	fi

	# Daca totul e in regula, atunci afisam liniile dorite
	if [[ $valid -eq 1 ]];then

		echo "$file: "

		# Iteram prin toate liniile fisierului si verificam
		# Facem cu < <( .. ) deoarece avem nevoie de variabile externe (freq)
		sed -n "/$word/p" "$file" | while read -r line; do

			# Numaram punem fiecare aparitie de word pe o linie noua
			# dupa care numaram liniile cu wc -l pentru a afla frecventa
			count=$(echo "$line" | grep -Eo "\<$word\>" | wc -l)

			# Daca frecventa este egala cu freq, afisam linia
			if [[ "$count" -eq "$freq" ]]; then
				echo "$line"
			fi

		# sed afiseaza fiecare linie care contine word
		done < <(sed -n "/$word/p" "$file")
	fi

	# Trecem peste argumentul curent si urmatoarele doua (un triplet)
	shift 3
	echo ""
done
