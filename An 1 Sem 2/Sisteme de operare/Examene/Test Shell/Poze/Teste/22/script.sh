#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 fisier_cuvinte"
	exit 1
fi

read -p "Introduceti numarul de cuvinte din propozitii: " n
read -rp "Introduceti numele fisierului: " name

size=$(wc -l < "$1")
i=1
j=1

while read -r cuvant; do
	prop="$prop $cuvant"
	if [[ $i -eq $n || $j -eq $size ]]; then
		i=1
		prop_corect=$(echo "$prop" | sed 's/ //')
		echo "$prop_corect." >> ${name}.txt
		prop=""
	else
		((i++))
	fi
	((j++))
done < $1

echo "Fisier: $name.txt"
linii=$(wc -l < "$name.txt")
cuvinte=$(wc -w < "$name.txt")
caractere=$(wc -c < "$name.txt")

echo "Linii: $linii Cuvinte: $cuvinte Caractere: $caractere"
