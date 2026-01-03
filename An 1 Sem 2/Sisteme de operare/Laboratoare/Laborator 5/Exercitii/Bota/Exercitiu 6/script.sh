#!/bin/bash

# Verificam sa avem minim un argument
if [ $# -eq 0 ]; then
	echo "Usage: $0 <arg1> <arg2> .. <argN>"
	exit 1
fi

# Citim cuvantul dorit
echo "Introduceti cuvantul pe care doriti sa il contorizati: "
read -r word

# Iteram prin fiecare fisier dat ca argument
for file in "$@"; do
	echo ""

	# Aflam numarul de aparitii a cuvantului in fisier
	# In loc de \< .. \> putem folosi -w pentru a capta doar daca e cuvant
	# Nu folosim grep -c din prima pentru ca el numara liniile unde apare cuvantul, nu aparitiile
	# Deci daca avem mai multe aparitii pe o linie, aia se va pune ca 1
	# grep -o ia fiecare aparitie si o pune pe o linie noua
	# In loc de grep -c putem folosi la fel de bine wc -l
	occurances=$(grep -Eo "\<$word\>" "$file" | grep -c "$word")
	
	echo "$file: $occurances"
done
