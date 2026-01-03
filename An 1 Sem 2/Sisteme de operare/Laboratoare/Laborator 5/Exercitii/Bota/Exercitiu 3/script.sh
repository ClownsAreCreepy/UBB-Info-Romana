#!/bin/bash

# Verificam sa existe un singur argument
if [ $# -ne 1 ]
then
	echo "Usage: $0 <argument>"
	exit 1
fi

# Verificam ca argumentul sa fie un director
if ! [ -d "$1" ]
then
	echo "Argument must be a directory!"
	exit 2
fi

# Initializam variabile globale
nr_fisiere=0
nr_linii_totale=0

# Nu folosim | while pentru ca nu se salveaza variabilele la iesire (se creeaza un subshell)
# Folosim < <(find ..) pentru a ni se salva variabilele globale
# <( .. ) inseamna ia output-u instructiunii din paranteze si trateaz-o ca un fisier
# Al doile < la done este pentru a redirectiona output-ul lui find in while
# Punem read -r pentru a lua si fisierele cu spatii in numele lor
while read -r line
	do
		# grep -q = nu afiseaza nimic, doar returneaza 1 daca a gasit ceva si 0 daca nu
		if file "$line" | grep -q "text"; 
		then
			# Nu punem $ la paranteze duble deoarece nu se returneaza nimic, doar mate
			((++nr_fisiere))
			nr_linii=$(wc -l < $line)
			((nr_linii_totale += nr_linii))
		fi
	done < <(find "$1" -maxdepth 1 -type f) 

# Verificam daca s-au gasit fisiere, ca sa nu impartim la 0
if [ $nr_fisiere -eq 0 ]
then
	echo "No files in directory $1!"
else
	# Punem $ la paranteze duble ca sa capturam rezultatul si sa il luam ca un string
	echo "$((nr_linii_totale / nr_fisiere))"
fi
