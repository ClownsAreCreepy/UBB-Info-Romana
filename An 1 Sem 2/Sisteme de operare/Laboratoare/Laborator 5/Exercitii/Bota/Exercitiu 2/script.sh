#!/bin/bash

# Verificam sa fie exact 1 argument
if [ $# -ne 1 ]
then
	echo "Usage: $0 <argument>"
	exit 1
fi

# Verificam ca argumentul sa fie un folder
if ! [ -d "$1" ]
then
	echo "Argument must be a directory!"
	exit 2
fi

# Verificam fisierele din directorul dat
find "$1" -type f | while read -r line
	do
		# Verificam sa fie de tip text
		if file "$line" | grep -q "text"; 
		then
			# Verificam daca numarul de linii este strict mai mare decat 6
			# Punem awk pentru ca wc -l arata "*nr_linii* *nume_fisier*"
			# Vrem sa luam doar numarul de linii, adica prima coloana
			if [ $(wc -l "$line" | awk '{print $1}') -gt 6 ]

			# Daca vrem fara awk, putem face
			#if [ $(wc -l < "$file") -gt 6 ]
			# Daca redirectam la wc numele fisierului, atunci nu mai arata numele
			then
				# Daca da, afisam primele si ultimele 3 linii din fisier
				head -n 3 "$line"
				tail -n 3 "$line"
			else
				# Daca nu, afisam intreg fisierul
				cat "$line"
			fi
		fi
	done
