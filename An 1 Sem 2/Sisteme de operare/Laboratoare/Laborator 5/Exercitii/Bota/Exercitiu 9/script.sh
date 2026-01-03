#!/bin/bash

# Verificam sa avem cel putin un argument
if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> .. <argN>"
	exit 1
fi

# Verificam ca toate argumentele sa fie fisiere valide
for arg in "$@"; do
	if ! [[ -f "$arg" ]]; then
		echo "All arguments must be valid files!"
		exit 2
	fi
done

# Iteram prin fiecare fisier si cautam linia cea mai frecventa
while [[ $# -ne 0 ]]; do
	file=$1

	# Sortam inainte deoarece uniq se uita doar la pozitii consecutive :(
	top_line=$(sort $file | uniq -c | sort -rn | head -n 1)

	# Avem o variabila unde concatenam toate cele-mai-frecvente-linii 
	lines+="$top_line"$'\n'
	
	# Trecem la argumentul (fisierul) urmator
	shift 
done

# Folosim ${ .. } pentru a elimina ultimele 2 caractere (\n) din rezultat
# ${ .. } e doar un operator de disambiguitate
# ${var}text = string-ul din var + text
# $vartext = string din vartext
lines=${lines::-2}

# Le afisam sortate descrescator dupa frecventa
echo "$lines" | sort -rn | sed -E 's/^[[:space:]]+[0-9]+[[:space:]]//'
